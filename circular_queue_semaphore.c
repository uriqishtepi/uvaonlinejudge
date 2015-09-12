/* this example builds a circular queue and uses a semaphore
 * to guard the critical section inside the mutex. 
 * If the queue is full, the producers sem_wait until they receive a msg
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
    int a;
    int available;
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
    assert(q->count >=0 && q->count <= QMAX);
    pthread_mutex_lock(&q->mutex);
    int loc = q->count;
    pthread_mutex_unlock(&q->mutex);

    return(loc == 0);
}

int is_full(queue *q)
{
    assert(q->count >=0 && q->count <= QMAX);
    pthread_mutex_lock(&q->mutex);
    int loc = q->count;
    pthread_mutex_unlock(&q->mutex);

    return(loc == QMAX);
}

int enqueue(queue *q, int a)
{
    pthread_mutex_lock(&q->mutex);

    int rc = 0;
    while(q->count == QMAX && rc == 0) {
        rc = pthread_cond_wait(&q->produce_more, &q->mutex);
    }
    
    q->arr[(q->front + q->count ) % QMAX] = a;
    q->count++;
    q->inserted++;

    assert(q->count >=0 && q->count <= QMAX);
    pthread_cond_signal(&q->consume_more);
    pthread_mutex_unlock(&q->mutex);
    return 0;
}

int dequeue(queue *q)
{
    pthread_mutex_lock(&q->mutex);
    int rc = 0;
    while(q->count == 0 && rc == 0) {
        rc = pthread_cond_wait(&q->consume_more, &q->mutex);
    }
    int oldfront = q->front;
    if(++q->front == QMAX)
        q->front = 0;
    q->count--;
    q->deleted++;
    assert(q->count >=0 && q->count <= QMAX);
    pthread_cond_signal(&q->produce_more);
    pthread_mutex_unlock(&q->mutex);
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
        printf("produce_work: tid=%llx, val=%d\n", THREADID, val);
        //usleep(1000*10);
    }
    return NULL;
}

void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    while(!done) {
        int val = dequeue(q);
        printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
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
    //test_q(&q);

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
    printf("Doing Work tid=%llx a=%d\n", THREADID, a);
    //usleep(1000*500);
}
