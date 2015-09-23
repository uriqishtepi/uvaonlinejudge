/* this example builds a circular queue and uses lockfree method
 * to guard the critical section where the queue parameters are modified.
 * We use a global variable as a lock, set it to one via testandset and
 * if successful we have lock and proceed into the critical section.
 * To unlock just set it to zero. Before critical section we do much
 * of the work optimistically, so that we will be for a very short time
 * inside the section. The advantage of this approach is that we don't 
 * make an OS call to lock mutex. The disadvantage is that if there is
 * a lot of contention, this will be slower than using a mutex due to
 * the fact that we do a lot of the work before finding out that we did
 * not get the lock. If there is a lot of contention, maybe we can 
 * simply deferr all the work after testandset.
 *
 * If the queue is full, return fail upon insert, and if the queue is empty
 * return -1 upon pop.
 * The do some work portion is built to test the validity of the algorithm
 * by making sure that we dont pop the same location more than once, and 
 * that we visit all numbers up to max.
 */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

extern void usleep(int);

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define QMAX 10

#define MAX_ITEMS 10000
#define MAX_ROUNDS 3
#ifndef __ATOMIC_SEQ_CST
#define __ATOMIC_SEQ_CST 2
#endif

unsigned char * bigarr;

enum { UNSEEN, ENQUEUED, PROCESSED };

struct queue_param {
    short int front;
    short int count;
};
typedef struct queue_param queue_param;

struct queue {
    long long int arr[QMAX];
    queue_param param;
    int inserts;
    int deletes;
#ifdef DEBUG
    int enqueue_redo;
    int dequeue_redo;
#endif
    char locked;
};

typedef struct queue queue;

void do_some_work(long long int);


/* circular queue is an array and a front and end pointer
 * we can enqueue as long as front - 1 != end (except end cases)
 * we can dequeue as long as front != end 
 */


int done = 0;

void queue_init(queue *q)
{
    memset(&q->param, 0, sizeof(q->param));
    q->locked = 0;
    q->inserts = 0;
    q->deletes = 0;

#ifdef DEBUG
    q->enqueue_redo = 0;
    q->dequeue_redo = 0;
#endif
}

void queue_stats(queue *q)
{
    printf("queue capacity %d, curr count %d\n", QMAX, q->param.count);
    printf("inserts %d, deletes %d\n", q->inserts, q->deletes);
#ifdef DEBUG
    printf("redos: enque %d, deque %d\n", q->enqueue_redo, q->dequeue_redo);
#endif
}

//the result is fleeting, it can change by another thread
int is_empty(queue *q)
{
    int loc = q->param.count;
    assert(loc >=0 && loc <= QMAX);

    return(loc == 0);
}

//the result is fleeting, it can change by another thread
int is_full(queue *q)
{
    int loc = q->param.count;
    assert(loc >=0 && loc <= QMAX);

    return(loc == QMAX);
}

int enqueue(queue *q, long long int el)
{
    queue_param oldparam;
    queue_param newparam;
    int redo = 0;

    int lastpos;
    do {
        oldparam = newparam = q->param;
        assert(newparam.count <= QMAX);
        if(newparam.count == QMAX) return -1; //queue full

        lastpos = (newparam.front + newparam.count ) % QMAX;
        newparam.count++;
    } while( __atomic_exchange_n((volatile char*) &q->locked, 1, __ATOMIC_SEQ_CST) == 1);
    /* now i have lock: 
     * if data has changed, need to redo that work */
    if( *(int*) &oldparam != *(int*) &q->param) 
    {
        newparam = q->param;
        assert(newparam.count <= QMAX);
        if(newparam.count == QMAX) {
            q->locked = 0; //allow other threads to go in
            return -1;
        }

        lastpos = (newparam.front + newparam.count ) % QMAX;
        newparam.count++;
    }

    /* the following two lines are the crucial piece of the critical section */
    q->arr[lastpos] = el;
    q->param = newparam;
    q->locked = 0; /* end of the critical section */

    printf("enqueue: tid=0x%llx, val=%lld, to=%d\n", THREADID, el, lastpos);
    //keep statistics of how many were inserted, add 1 to count
    __atomic_add_fetch(&q->inserts, 1, __ATOMIC_SEQ_CST);
#ifdef DEBUG
    __atomic_add_fetch(&(q->enqueue_redo), redo, __ATOMIC_SEQ_CST);
#endif
    return 0;
}

long long int dequeue(queue *q)
{
    queue_param oldparam;
    queue_param newparam;
    long long int saved_back;
    int redo = 0;

    do {
        oldparam = newparam = q->param;
        if(newparam.count == 0) return -1; //queue empy

        newparam.front++;
        if( newparam.front == QMAX) 
            newparam.front = 0;
        newparam.count--;
    }
    while( __atomic_exchange_n((volatile char*) &q->locked, 1, __ATOMIC_SEQ_CST) == 1);

    /* if data has changed, need to redo that work */
    if( *(int*) &oldparam != *(int*) &q->param) 
    {
        newparam = q->param;

        if(newparam.count == 0) {
            q->locked = 0; //allow other threads to go in
            return -1; //queue empy
        }

        newparam.front++;
        if( newparam.front == QMAX) 
            newparam.front = 0;
        newparam.count--;
    }

    /* next two lines are the crucial piece of the critical section */
    saved_back = q->arr[q->param.front];
    q->param = newparam;
    q->locked = 0; /* end of the critical section */

    printf("dequeue: tid=0x%llx, oldparam=%lld, from=%d\n", THREADID, saved_back, oldparam.front);
    __atomic_add_fetch(&q->deletes, 1, __ATOMIC_SEQ_CST);
#ifdef DEBUG
    __atomic_add_fetch(&q->dequeue_redo, redo, __ATOMIC_SEQ_CST);
#endif
    return saved_back; //need saved val, otherwise there's no guarantee
}

inline void checkloc(int offset, int newtowrite, int shouldhavebeen);

void checkloc(int offset, int newtowrite, int shouldhavebeen)
{
    long long int tmp = __atomic_exchange_n(&bigarr[offset], newtowrite, __ATOMIC_SEQ_CST);
    if(shouldhavebeen != tmp) 
        printf("Should be %d but is %lld, offset=%d\n", shouldhavebeen, tmp, offset);
    assert(shouldhavebeen == tmp); 
}

void * produce_work(void * arg)
{
    queue *q = (queue *) arg;
    static int counter = 0;
    static int round = 0;
    static int finishers = 0;
    while(!done) {
        int val = __atomic_add_fetch(&counter, 1, __ATOMIC_SEQ_CST);
        if(val <= MAX_ITEMS) {
            printf("produce_work: tid=0x%llx, val=%d counter=%d\n", THREADID, val, counter);
            checkloc(val, ENQUEUED, UNSEEN);

            while( !done && enqueue(q, val) != 0) {} //enqueue returns -1 on queue full
        }
        else {
            int locfin = __atomic_add_fetch(&finishers, 1, __ATOMIC_SEQ_CST);
            printf("produce_work: tid=0x%llx, locfin=%d\n", THREADID, locfin);
                
            while( finishers < THREADNUM ) {
                 printf("produce_work: tid=0x%llx, finishers=%d\n", THREADID, finishers);
                 sleep(1); //wait for all other threads to be done
            }
            
            if(locfin < THREADNUM) {
                while( finishers != 0 ) { // wait until finishers is set back to 0
                    printf("waiting for check: tid=0x%llx\n", THREADID);
                    usleep(1000);
                }
                continue;
            }

            //who was the last to increment finishers will do more work
            while( !is_empty(q))
                    sleep(1);   //wait for dequeuers
            sleep(1);   //wait for dequeuers

            {   //check that all elements are visited
                for(int j=1; j<=MAX_ITEMS; j++) 
                    checkloc(j, UNSEEN, PROCESSED);

                if(++round >= MAX_ROUNDS) 
                    done = 1;
                else {
                    printf("reseting to zero: tid=0x%llx\n", THREADID);
                    counter = 0;
                }
                finishers = 0; /* allow others to go to top of while loop */
            }
        }
    }
    return NULL;
}


void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    long long int val = 0;
    while(val >= 0 || !done) {
        val = dequeue(q); //dequeue returns -1 on queue empty
        if(val < 0) continue;

        printf("consume_work: tid=0x%llx, val=%lld\n", THREADID, val);
        do_some_work(val);
        //if(done) usleep(10);

        //usleep(1);
    }
    return NULL;
}



void test_q(queue *q)
{

    long long int blah = 1;
    long long int newblah = blah + 1;
    printf("blah blah =%lld\n", blah);
    __sync_bool_compare_and_swap(&(blah), newblah, newblah);
    printf("blah blah =%lld\n", blah);


    assert(is_empty(q) == 1);
    enqueue(q, 1);
    assert(is_empty(q) == 0);
    long long int val = dequeue(q);
    assert(val == 1);
    assert(is_empty(q) == 1);

    for(int i = 0; i < 1000; i++) {
        assert(is_empty(q) == 1);
        enqueue(q, i);
        assert(is_empty(q) == 0);
        long long int val = dequeue(q);
        assert(val == i);
    }
    assert(is_empty(q) == 1);
    
    for(int i = 0; i < 30; i++) {
        int val = enqueue(q, i);
        assert((i < QMAX && val == 0) || (i >= QMAX && val == -1));
    }
    for(int i = 0; i < 30; i++) {
        long long int val = dequeue(q);
        assert((i < QMAX && val == i) || (i >= QMAX && val == -1));
    }
}


void multithreaded_test()
{
    struct timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);

    //call bunch of threads to do some enqueing and some dequeing+work 
    pthread_t thv[2*THREADNUM];
    queue q;
    queue_init(&q);
    bigarr = calloc(MAX_ITEMS, 1);

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, produce_work, &q);
    }
    
    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[THREADNUM+i], NULL, consume_work, &q);
    }

    FORL(j, 0, 2*THREADNUM - 1) {
        pthread_join(thv[j], NULL);
    }

    queue_stats(&q);
    free (bigarr);
}

int main()
{
    /*
    {
    queue q0;
    queue_init(&q0);
    test_q(&q0);
    } */

    multithreaded_test();

    return 0;
}

void do_some_work(long long int val)
{
    //printf("Doing Work tid=0x%llx a=%d\n", THREADID, a);

    //struct timespec smalltime = { .tv_sec = 0, .tv_nsec = 1 };
    //nanosleep(&smalltime, NULL);
    //usleep(10);

    checkloc(val, PROCESSED, ENQUEUED);
}
