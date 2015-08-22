/* this example builds a circular queue and uses conditional variable
 * and a mutex to guard the critical section inside the mutex. 
 * If the queue is full, the producers wait until they receive a msg
 * that there is room in the queue. If the queue is empty the consumers 
 * sleep until they receive a signal that there is something in the queue
 * This way cpu does not get occupied in spinning but rather in doing 
 * useful work.
 */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100
#define QMAX 20

#define MAX_ITEMS 10000000
#define MAX_ROUNDS 10

unsigned char * bigarr;

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
};

typedef struct queue queue;

void do_some_work(int);


/* circular queue is an array and a front and end pointer
 * we can enqueue as long as front - 1 != end (except end cases)
 * we can dequeue as long as front != end 
 */


int done = 0;

void queue_init(queue *q)
{
    memset(&q->param, 0, sizeof(q->param));
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

int enqueue(queue *q, int el)
{
    queue_param newval;
    queue_param oldval;
    int redo = 0;

    do 
    {
#ifdef DEBUG
        redo++;
#endif
        //read front/count at once -- queue_param has same size as int
        int tmp = __atomic_load_n( (int *) &(q->param), __ATOMIC_SEQ_CST);
        oldval = *((queue_param*) &tmp);
        assert(oldval.count <= QMAX);
        if(oldval.count == QMAX) 
            return -1;

        q->arr[(oldval.front + oldval.count ) % QMAX] = el;
        newval = oldval; //make copy, modify the count part
        newval.count++;
    } while(!__atomic_compare_exchange(((queue_param *)&(q->param)), &oldval, &newval, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));

    //keep statistics of how many were inserted, add 1 to count
    int inserts = __atomic_add_fetch(&q->inserts, 1, __ATOMIC_SEQ_CST);
#ifdef DEBUG
    __atomic_add_fetch(&(q->enqueue_redo), redo, __ATOMIC_SEQ_CST);
#endif
    return 0;
}

int dequeue(queue *q)
{
    queue_param newval;
    queue_param oldval;
    int saved_back;
    int redo = 0;

    do {
#ifdef DEBUG
        redo++;
#endif
        //read front/count at once -- queue_param has same size as int
        int tmp = __atomic_load_n( (int *) &(q->param), __ATOMIC_SEQ_CST);
        oldval = *((queue_param*) &tmp);

        if(oldval.count == 0) return -1; //queue empy

        newval = oldval;
        if( ++newval.front == QMAX) 
            newval.front = 0;
        newval.count--;  

        saved_back = q->arr[oldval.front];
    } while(!__atomic_compare_exchange(((queue_param *)&(q->param)), &oldval, &newval, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));

    int deletes = __sync_add_and_fetch(&q->deletes, 1);
#ifdef DEBUG
    __atomic_add_fetch(&q->dequeue_redo, redo, __ATOMIC_SEQ_CST);
#endif
    return saved_back; //need saved val, otherwise there's no guarantee
}



void * produce_work(void * arg)
{
    queue *q = (queue *) arg;
    static int counter = 0;
    static int round = 0;
    while(!done) {
        int i = __atomic_add_fetch(&counter, 1, __ATOMIC_SEQ_CST);
        if(i < MAX_ITEMS) {
            bigarr[i] = 1;
            enqueue(q, i);
        }
        else {
            int zero = 0;
            int res = __atomic_compare_exchange(&counter, &i, &zero, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
            if(res) { //we were the winner thread to perform change
                if(round++ > MAX_ROUNDS) 
                    done = 1;
            }
            printf("reseting to zero: tid=%llx, res=%d\n", THREADID, res);
        }
        //printf("produce_work: tid=%llx, val=%d\n", THREADID, val);
        //usleep(1000*10);
    }
    return NULL;
}


void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    int val = 0;
    while(val >= 0 || !done) {
        val = dequeue(q);
        if(val < 0) continue;

        //printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
        do_some_work(val);
        if(done)
            usleep(10);
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
    int val = dequeue(q);
    assert(val == 1);
    assert(is_empty(q) == 1);

    for(int i = 0; i < 1000; i++) {
        assert(is_empty(q) == 1);
        enqueue(q, i);
        assert(is_empty(q) == 0);
        int val = dequeue(q);
        assert(val == i);
    }
    assert(is_empty(q) == 1);
    
    for(int i = 0; i < 30; i++) {
        int val = enqueue(q, i);
        assert((i < QMAX && val == 0) || (i >= QMAX && val == -1));
    }
    for(int i = 0; i < 30; i++) {
        int val = dequeue(q);
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
}

int main()
{
    {
    queue q0;
    queue_init(&q0);
    test_q(&q0);
    }

    multithreaded_test();

    return 0;
}

void do_some_work(int a)
{
    //printf("Doing Work tid=%llx a=%d\n", THREADID, a);

    //struct timespec smalltime = { .tv_sec = 0, .tv_nsec = 1 };
    //nanosleep(smalltime);

    int val = 2; //will put 2
    __atomic_exchange_n(&val, bigarr[a], __ATOMIC_SEQ_CST);
    assert(1 == val); //what we read should be 1
}
