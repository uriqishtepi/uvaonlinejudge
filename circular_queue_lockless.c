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
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100
#define QMAX 20

struct queue {
    int arr[QMAX];
    int front;
    int count;
    int inserted;
    int deleted;
    pthread_mutex_t mutex;
    pthread_cond_t produce_more;
    pthread_cond_t consume_more;
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
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->produce_more, NULL);
    pthread_cond_init(&q->consume_more, NULL);

    q->front = 0;
    q->count = 0;
    q->inserted = 0;
    q->deleted = 0;
}

int is_empty(queue *q)
{
    int loc = q->count;
    assert(loc >=0 && loc <= QMAX);

    return(loc == 0);
}

int is_full(queue *q)
{
    assert(q->count >=0 && q->count <= QMAX);
    int loc = q->count;

    return(loc == QMAX);
}

int enqueue(queue *q, int a)
{
    long long int twocountrs;
    long long int oldval;
    //do 
    {
        //read front/count at once in one variable
        twocountrs = *(long long int*) (&q->count); 
        oldval = twocountrs;
        printf("old front =%d, count =%d\n", ((int*) (&oldval)) [0], ((int*) (&oldval)) [1]);
        ((int*) (&twocountrs)) [1] ++; //count ++
        printf("old front =%d, count =%d\n", ((int*) (&twocountrs)) [0], ((int*) (&twocountrs)) [1]);

        printf("oldorig front =%d, count =%d\n", q->front, q->count);
    } 
    //while(__sync_bool_compare_and_swap(&(q->count), oldval, twocountrs));
    __sync_bool_compare_and_swap(&(q->count), oldval, twocountrs);
    printf("neworig front =%d, count =%d\n", q->front, q->count);
    int front = ((int*) (&oldval)) [0];
    int count = ((int*) (&oldval)) [1];
    //change the value of the memory area -- no one else is working on this 
    q->arr[(front + count ) % QMAX] = a;

    int inserted;
    int oldins;
    do {
        inserted = q->inserted;
        oldins = inserted;
        inserted++;
        printf("oldorig inserted =%d\n", q->inserted);
    } while(!__sync_bool_compare_and_swap((&q->inserted), oldins, inserted));

    printf("neworig inserted =%d\n", q->inserted);
    front = ((int*) (&twocountrs)) [0];
    count = ((int*) (&twocountrs)) [1];
    assert(count >=0 && count <= QMAX);
    assert(q->count >=0 && q->count <= QMAX);
    return 0;
}

int dequeue(queue *q)
{
    int oldfront = q->front;
    if(++q->front == QMAX)
        q->front = 0;
    q->count--;
    q->deleted++;
    assert(q->count >=0 && q->count <= QMAX);

    return q->arr[oldfront];
}


void test_q(queue *q)
{
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
    test_q(&q);
    return 0;

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
