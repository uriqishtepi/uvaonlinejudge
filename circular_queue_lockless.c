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

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100
#define QMAX 20

struct queue_param {
    int front;
    int count;
    int inserted;
    int deleted;
};
typedef struct queue_param queue_param;

struct queue {
    int arr[QMAX];
    queue_param param;
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
}

int is_empty(queue *q)
{
    int loc = q->param.count;
    assert(loc >=0 && loc <= QMAX);

    return(loc == 0);
}

int is_full(queue *q)
{
    int loc = q->param.count;
    assert(loc >=0 && loc <= QMAX);

    return(loc == QMAX);
}

int enqueue(queue *q, int a)
{
    long long int newval;
    long long int oldval;

    do 
    {
        //read front/count at once in one variable
        //can i rely on memcpy to read in one shot? no, it reads
        //one byte at atime and that might not be fine at all.

        //memcpy(&oldval, &q->param, sizeof(oldval));
        //need atomic fetch here:
        oldval = __atomic_load_n( (long long int *) &(q->param), __ATOMIC_SEQ_CST);

        int front = ((int*) (&oldval)) [0];
        int count = ((int*) (&oldval)) [1];

        if(count == QMAX) 
            return -1;

        q->arr[(front + count ) % QMAX] = a;
        newval = oldval; //make copy, modify the count part
        ((int*) &newval)[1]++;  //count

        //printf("old front =%d, count =%d\n", ((int*) (&oldval)) [0], ((int*) (&oldval)) [1]);

        //printf("oldorig front =%d, count =%d\n", q->param.front, q->param.count);
    } while(!__atomic_compare_exchange(((long long int *)&(q->param)), &oldval, &newval, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
    //printf("neworig front =%d, count =%d\n", q->param.front, q->param.count);
    /*change the value of the memory area -- no one else is working on this 
    //this is wrong, what if just after our CAS succeeded, another thread goes in and 
    //dequeues this element (say there was only one in the queue, 
    //but we have not assigned the content yet. the assignment has to be 
    //in the CAS, otherwise there is no guranantee
    q->arr[(front + count ) % QMAX] = a;
    */

    //keep statistics of how many were inserted
    int inserted = __atomic_add_fetch(&q->param.inserted, 1, __ATOMIC_SEQ_CST);

    printf("inserted =%d\n", inserted);

    int count = ((int*) (&newval)) [1];
    assert(count >=0 && count <= QMAX);
    //this will not work: assert(q->param.count >=0 && q->param.count <= QMAX);
    return 0;
}

int dequeue(queue *q)
{
    long long int newval;
    long long int oldval;
    int saved_back;

    do {
        //read front/count at once in one variable
        oldval = __atomic_load_n( (long long int *) &(q->param), __ATOMIC_SEQ_CST);
        if(((int*) &oldval)[1] == 0) return -1;
        newval = oldval;
        if(++ ((int*) &newval)[0] == QMAX) //front
            ((int*) &newval)[0] = 0;
        ((int*) &newval)[1]--;  //count

        int oldfront = ((int*) (&oldval)) [0]; //save value
        saved_back = q->arr[oldfront];
        //printf("old front =%d, count =%d\n", ((int*) (&oldval)) [0], ((int*) (&oldval)) [1]);

        //printf("oldorig front =%d, count =%d\n", q->param.front, q->param.count);
    } while(!__sync_bool_compare_and_swap(((long long int *)&(q->param)), oldval, newval));
    //printf("neworig front =%d, count =%d\n", q->param.front, q->param.count);

    int deleted = __sync_add_and_fetch(&q->param.deleted, 1);
    printf("deleted =%d\n", deleted);

    int count = ((int*) (&newval)) [1];
    assert(count >=0 && count <= QMAX);
    //this will not work: assert(q->param.count >=0 && q->param.count <= QMAX);
    return saved_back; //need saved val, otherwise there's no guarantee
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


void * produce_work(void * arg)
{
    queue *q = (queue *) arg;
    while(!done) {
        int val = rand();
        enqueue(q, val);
        //printf("produce_work: tid=%llx, val=%d\n", THREADID, val);
        //usleep(1000*10);
    }
    return NULL;
}

void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    while(!done) {
        int val = dequeue(q);
        //printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
        do_some_work(val);
        //usleep(1000*10);
    }
    return NULL;
}

int main()
{
    struct timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);

    //call 10 threads to do some work 
    pthread_t thv[2*THREADNUM];
    queue q;
    queue_init(&q);

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, produce_work, &q);
    }
    
    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, consume_work, &q);
    }

    FORL(j, 0, 2*THREADNUM) {
        void *val;
        pthread_join(thv[j], &val);
    }
    return 0;
}

void do_some_work(int a)
{
    //printf("Doing Work tid=%llx a=%d\n", THREADID, a);
    //usleep(1000*500);
}
