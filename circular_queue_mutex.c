/* this example builds a circular queue and uses a mutex to guard
 * the critical section inside the mutex. 
 * If the queue is full, the producers have to spin and to reaquire
 * lock in order to synchronize access to the critical section.
 * Thus the issue with this approach is the wasted cpu cycles while 
 * we are waiting for work to be done and for the queue to become 
 * empty. 
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
#define MAX_ITEMS 1000
#define MAX_ROUNDS 2

struct queue {
    int a;
    int available;
    int arr[QMAX];
    int front;
    int count;
    int inserted;
    int deleted;
    pthread_mutex_t mutex;
};

typedef struct queue queue;

void do_some_work(int);


/* circular queue is an array and a front and end pointer
 * we can enqueue as long as front - 1 != end (except end cases)
 * we can dequeue as long as front != end 
 */


unsigned char * bigarr;
int gbl_exit = 0;
int gbl_val = 0;
    pthread_mutex_t gbl_val_mutex;

void queue_init(queue *q)
{
    pthread_mutex_init(&q->mutex, NULL);

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
    if(q->count == QMAX || gbl_exit) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    printf("enqueue LOCK: tid=%llx, val=%d\n", THREADID, a);
    
    q->arr[(q->front + q->count ) % QMAX] = a;
    q->count++;
    q->inserted++;

    assert(q->count >=0 && q->count <= QMAX);
    pthread_mutex_unlock(&q->mutex);
    return 0;
}

int dequeue(queue *q, int * val)
{
    pthread_mutex_lock(&q->mutex);
    if(q->count == 0 || gbl_exit) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    int oldfront = q->front;
    if(++q->front == QMAX)
        q->front = 0;
    q->count--;
    q->deleted++;
    assert(q->count >=0 && q->count <= QMAX);
    *val = q->arr[oldfront];
    int savedcount = q->count;
    pthread_mutex_unlock(&q->mutex);
    printf("denquey UNLOCK: tid=%llx, val=%d,q->count=%d\n", THREADID, *val, savedcount);
    return 0;
}

void * produce_work(void * arg)
{
    queue *q = (queue *) arg;
    static int round = 0;
    while(!gbl_exit) {
        pthread_mutex_lock(&gbl_val_mutex);
        int i = gbl_val++;
        pthread_mutex_unlock(&gbl_val_mutex);
        if(gbl_exit) break;
        if(i < MAX_ITEMS) {
            int tmp = bigarr[i];
            bigarr[i] = 1;
            if(0 != tmp) printf("Should be 0 but is %d, i=%d\n", tmp, i);
            assert(0 == tmp); 
            while(enqueue(q, i) == -1 && !gbl_exit) { } //retry
            usleep(1);
        }
        else if(i == MAX_ITEMS) {
            usleep(10000); //give a chance to others to finish
            for(int j=0; j<MAX_ITEMS; j++) {
                int tmp = bigarr[j];
                bigarr[j] = 0;
                if(2 != tmp) printf("Should be 2 but is %d, j=%d\n", tmp, j);
                assert(2 == tmp); //what we read should be 2
            }
            if(++round >= MAX_ROUNDS) {
                gbl_exit = 1;
            }
            else
                printf("reseting to zero: tid=%llx\n", THREADID);

            pthread_mutex_lock(&gbl_val_mutex);
            gbl_val =0;
            pthread_mutex_unlock(&gbl_val_mutex);
        }
        else usleep(10000);
    }
    return NULL;
}

void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    int val;
    int rc = dequeue(q, &val);
    while(!gbl_exit) {
        if(rc == 0) { 
            printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
            do_some_work(val);
        }
        else usleep(100);
        rc = dequeue(q, &val);
    }
    return NULL;
}


void test_q(queue *q)
{
    assert(is_empty(q) == 1);
    enqueue(q, 1);
    assert(is_empty(q) == 0);
    int val;
    int rc = dequeue(q, &val);
    assert(val == 1);
    assert(is_empty(q) == 1);

    for(int i = 0; i < 1000; i++) {
        assert(is_empty(q) == 1);
        enqueue(q, i);
        assert(is_empty(q) == 0);
        int rc = dequeue(q, &val);
        assert(rc == 0 && val == i);
    }
    assert(is_empty(q) == 1);
    
    for(int i = 0; i < 30; i++) {
        int val = enqueue(q, i);
        assert((i < QMAX && val == 0) || (i >= QMAX && val == -1));
    }
    for(int i = 0; i < 30; i++) {
        int rc = dequeue(q, &val);
        assert((i < QMAX && val == i) || (i >= QMAX && rc == -1));
    }
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
    bigarr = calloc(MAX_ITEMS+1, 1);
    pthread_mutex_init(&gbl_val_mutex, NULL);
    //test_q(&q);

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, produce_work, &q);
    }
    
    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[THREADNUM+i], NULL, consume_work, &q);
    }

    FORL(j, 0, 2*THREADNUM-1) {
        pthread_join(thv[j], NULL);
    }
    free (bigarr);
    return 0;
}

void do_some_work(int val)
{
    printf("Doing Work tid=%llx a=%d\n", THREADID, val);
    //usleep(1000*500);
    int tmp = bigarr[val];
    bigarr[val] = 2;
    if(1 != tmp) printf("Should be 1 but is %d, val=%d\n", tmp, val);
    assert(1 == tmp); //what we read should be 1
}
