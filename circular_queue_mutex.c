/* this example builds a circular queue and uses a mutex to guard
 * the critical section inside the mutex. 
 * If the queue is full, the producers have to spin and to reaquire
 * lock in order to synchronize access to the critical section.
 * Thus the issue with this approach is the wasted cpu cycles while 
 * we are waiting for work to be done and for the queue to become 
 * empty. 
 *
 * I'm complicating the condition because i want to have it do some work, 
 * stop doing work, do some more work, stop doing work, until some max 
 * is reached. To do that, i need to have finishing conditions to go thru 
 * state machine with the states: 
 * ready -> running -> producer_done -> consumer_done -> {exit, running}
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 3
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
enum state { s_running, s_doneproducing, s_doneconsuming, s_exit };
int gbl_state = 0;
int gbl_val = 0;
int gbl_doneproducers = 0;
int gbl_doneconsumers = 0;
pthread_mutex_t gbl_val_mutex;
pthread_mutex_t gbl_state_mutex;

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
    if(q->count == QMAX || gbl_state == s_exit) 
        return -1; //shortcut
    pthread_mutex_lock(&q->mutex);
    if(q->count == QMAX || gbl_state == s_exit) {
        pthread_mutex_unlock(&q->mutex);
        return -1;
    }
    q->arr[(q->front + q->count ) % QMAX] = a;
    q->count++;
    q->inserted++;

    assert(q->count >=0 && q->count <= QMAX);
    pthread_mutex_unlock(&q->mutex);
    printf("enqueue LOCK: tid=%llx, val=%d\n", THREADID, a);
    
    return 0;
}

int dequeue(queue *q, int * val)
{
    if(q->count == 0 || gbl_state == s_exit)
        return -1; //shortcut
    pthread_mutex_lock(&q->mutex);
    if(q->count == 0 || gbl_state == s_exit) {
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

void check_and_reset_bigarr(int * round) 
{
    while(gbl_state != s_doneconsuming)
        usleep(100); //give a chance to others to finish

    usleep(100); //give a chance to others to finish
    for(int j=0; j<MAX_ITEMS; j++) {
        int tmp = bigarr[j];
        bigarr[j] = 0;
        if(2 != tmp) printf("Should be 2 but is %d, j=%d\n", tmp, j);
        assert(2 == tmp); //what we read should be 2
    }
    if(++(*round) >= MAX_ROUNDS) {
        gbl_state = s_exit;
    }
    else {
        printf("reseting to zero: tid=%llx\n", THREADID);
        gbl_val = 0;
        gbl_state = s_running;
    }
}


void * produce_work(void * arg)
{
  queue *q = (queue *) arg;
  static int round = 0;
  while(gbl_state != s_exit) {
    if(gbl_state != s_running) {
        usleep(10000);
        continue;
    }

    pthread_mutex_lock(&gbl_val_mutex);
    int loc_val = gbl_val++;
    pthread_mutex_unlock(&gbl_val_mutex);
    if(gbl_state == s_exit) break;

    if( __builtin_expect(loc_val < MAX_ITEMS, 1) ) {
        int tmp = bigarr[loc_val];
        bigarr[loc_val] = 1;
        if(0 != tmp) printf("Should be 0 but is %d, loc_val=%d\n", tmp, loc_val);
        assert(0 == tmp); 
        while(enqueue(q, loc_val) == -1 && gbl_state != s_exit) { sched_yield(); } //retry
        usleep(1);
    }
    else {
        pthread_mutex_lock(&gbl_state_mutex);
        int ndone = ++gbl_doneproducers;
        pthread_mutex_unlock(&gbl_state_mutex);

        if(ndone == THREADNUM) {
            pthread_mutex_lock(&gbl_state_mutex);
            gbl_state = s_doneproducing;
            gbl_doneproducers = 0;
            pthread_mutex_unlock(&gbl_state_mutex);
        }

        if(loc_val == MAX_ITEMS) { //only one thread will come here
            check_and_reset_bigarr(&round);
        }
    }
  }
  return NULL;
}

void * consume_work(void * arg)
{
    queue *q = (queue *) arg;
    int n_done = 0;
    while(gbl_state != s_exit) 
    {
        if(gbl_state != s_running && gbl_state != s_doneproducing) {
            usleep(10000);
            continue;
        }

        int val;
        int rc = dequeue(q, &val);
        if(rc == 0) { 
            printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
            do_some_work(val);
            continue;
        }
        else {

            //else there was nothing to retrieve
            if(gbl_state != s_doneproducing) {
                usleep(1); //give chance to producers
                continue;
            }

            // nothing in queue and state is done producing: producers are done
            if(n_done == 0) {
                pthread_mutex_lock(&gbl_state_mutex);
                n_done = ++gbl_doneconsumers;
                pthread_mutex_unlock(&gbl_state_mutex);
            }

            if(n_done == THREADNUM) {
                gbl_doneconsumers = 0;
                gbl_state = s_doneconsuming;
            }
        }
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
    pthread_mutex_init(&gbl_state_mutex, NULL);
    //test_q(&q);
    gbl_state = s_running; //initial state

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
