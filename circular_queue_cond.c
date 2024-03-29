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
extern void usleep(int);

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100
#define QMAX 20
#define MAX_ITEMS 10000
#define MAX_ROUNDS 10
enum { UNSEEN, ENQUEUED, PROCESSED };

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


unsigned char *bigarr;
int gbl_exit = 0;
int gbl_val = 0;
pthread_mutex_t gbl_val_mutex;

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

//this is anuseless call because queu can change right after this call
int is_empty(queue *q)
{
    assert(q->count >=0 && q->count <= QMAX);
    //useless because it can change pthread_mutex_lock(&q->mutex);
    int loc = q->count;
    //pthread_mutex_unlock(&q->mutex);

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
    printf("enqueue: tid=%llx, val=%d\n", THREADID, a);
    pthread_mutex_lock(&q->mutex);

    int rc = 0;
    while(q->count == QMAX && rc == 0) {
        rc = pthread_cond_wait(&q->produce_more, &q->mutex);
        if(gbl_exit) { 
            pthread_mutex_unlock(&q->mutex);
            return -1;
        }
    }
    printf("enqueue LOCK: tid=%llx, val=%d\n", THREADID, a);

    q->arr[(q->front + q->count ) % QMAX] = a;
    q->count++;
    q->inserted++;

    assert(q->count >=0 && q->count <= QMAX);
    printf("enquey UNLOCK: tid=%llx, val=%d,q->count=%d\n", THREADID, a, q->count);

    pthread_mutex_unlock(&q->mutex);
    pthread_cond_signal(&q->consume_more);
    return 0;
}

int dequeue(queue *q)
{
    pthread_mutex_lock(&q->mutex);
    int rc = 0;
    while(q->count == 0 && rc == 0) {
        rc = pthread_cond_wait(&q->consume_more, &q->mutex);
        if(gbl_exit) { 
            pthread_mutex_unlock(&q->mutex);
            return -1;
        }
    }
    printf("denqueue LOCK: tid=%llx\n", THREADID);
    int oldfront = q->front;
    if(++q->front == QMAX)
        q->front = 0;
    q->count--;
    q->deleted++;
    assert(q->count >=0 && q->count <= QMAX);
    int savedval = q->arr[oldfront];
    int savedcount = q->count;

    pthread_mutex_unlock(&q->mutex);
    pthread_cond_signal(&q->produce_more);
    printf("denquey UNLOCK: tid=%llx, savedval=%d,q->count=%d\n", THREADID, savedval, savedcount);
    return savedval;
}


inline void checkloc(int offset, int newtowrite, int shouldhavebeen);

void checkloc(int offset, int newtowrite, int shouldhavebeen)
{
    int tmp = bigarr[offset];
    bigarr[offset] = newtowrite;
    if(shouldhavebeen != tmp) 
        printf("Should be %d but is %d, offset=%d\n", shouldhavebeen, tmp, offset);
    assert(shouldhavebeen == tmp); 
}


void *produce_work(void *arg)
{
    queue *q = (queue *) arg;
    static int round = 0;
    while(!gbl_exit) {
        pthread_mutex_lock(&gbl_val_mutex);
        int i = ++gbl_val;
        pthread_mutex_unlock(&gbl_val_mutex);
        if(gbl_exit) break;
        if(i <= MAX_ITEMS) {
            checkloc(i, ENQUEUED, UNSEEN);
            enqueue(q, i); //blocks till can insert
            usleep(1);
        }
        else {
            pthread_mutex_lock(&gbl_val_mutex);
            if(gbl_val < MAX_ITEMS) { //another thread did this part of work
                pthread_mutex_unlock(&gbl_val_mutex);
                continue;
            }
            usleep(10000); //give a chance to others to finish !!holding lock!!
            gbl_val =0;
            for(int j=1; j<=MAX_ITEMS; j++) {
                checkloc(j, UNSEEN, PROCESSED);
            }
            if(++round >= MAX_ROUNDS) {
                gbl_exit = 1;
                pthread_cond_broadcast(&q->consume_more); //broadcast to have them exit
                pthread_cond_broadcast(&q->produce_more);
            }
            else
                printf("reseting to zero: tid=%llx\n", THREADID);

            pthread_mutex_unlock(&gbl_val_mutex);
        }
    }
    return NULL;
}

void *consume_work(void *arg)
{
    queue *q = (queue *) arg;
    int val = dequeue(q);
    while(!gbl_exit) {
        printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
        do_some_work(val);
        val = dequeue(q);
        //usleep(1000*10);
    }
    return NULL;
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

    FORL(i, 0, THREADNUM) {
        pthread_join(thv[i], NULL);
    }
    FORL(i, 0, THREADNUM) {
        pthread_cancel(thv[THREADNUM+i]);
    }
    free (bigarr);
    return 0;
}

void do_some_work(int val)
{
    printf("Doing Work tid=%llx a=%d\n", THREADID, val);
    //usleep(1000*500);
    checkloc(val, PROCESSED, ENQUEUED);
}
