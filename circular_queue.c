#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100

struct thrd_param {
    int a;
    int available;
    pthread_mutex_t mutex;
    pthread_cond_t reader_ready;
    pthread_cond_t writer_ready;
};

typedef struct thrd_param thrd_param;

void do_some_work(int);


/* circular queue is an array and a front and end pointer
 * we can enqueue as long as front - 1 != end (except end cases)
 * we can dequeue as long as front != end 
 */

#define QMAX 20

int arr[QMAX];
int q_front = 0;
int q_count = 0;

int done = 0;


int is_empty()
{
    assert(q_count >=0 && q_count <= QMAX);
    return(q_count == 0);
}

int is_full()
{
    assert(q_count >=0 && q_count <= QMAX);
    return(q_count == QMAX);
}
int enqueue(int a)
{
    if(q_count == QMAX)
        return -1;
    
    arr[(q_front + q_count ) % QMAX] = a;
    q_count++;

    assert(q_count >=0 && q_count <= QMAX);
    return 0;
}

int dequeue()
{
    if(q_count == 0)
        return -1;
    int oldfront = q_front;
    if(++q_front == QMAX)
        q_front = 0;
    q_count--;
    assert(q_count >=0 && q_count <= QMAX);
    return arr[oldfront];
}


void test_q()
{
    assert(is_empty() == 1);
    enqueue(1);
    assert(is_empty() == 0);
    int val = dequeue();
    assert(val == 1);
    assert(is_empty() == 1);

    for(int i = 0; i < 1000; i++) {
        assert(is_empty() == 1);
        enqueue(i);
        assert(is_empty() == 0);
        int val = dequeue();
        assert(val == i);
    }
    assert(is_empty() == 1);
    
    for(int i = 0; i < 30; i++) {
        int val = enqueue(i);
        assert((i < QMAX && val == 0) || (i >= QMAX && val == -1));
    }
    for(int i = 0; i < 30; i++) {
        int val = dequeue();
        assert((i < QMAX && val == i) || (i >= QMAX && val == -1));
    }
}


void * produce_work(void * arg)
{
    while(!done) {
        if(!is_full()) {
            int val = rand();
            enqueue(val);
            //printf("produce_work: tid=%llx, val=%d\n", THREADID, val);
        }
        //usleep(1000*10);
    }
    return NULL;
}

void * consume_work(void * arg)
{
    while(!done) {
        int val = dequeue();
        //printf("consume_work: tid=%llx, val=%d\n", THREADID, val);
        if(val >= 0) {
            do_some_work(val);
        }
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
    //test_q();
    pthread_t thv[2*THREADNUM];
    thrd_param p;
    pthread_mutex_init(&p.mutex, NULL);
    pthread_cond_init(&p.reader_ready, NULL);
    pthread_cond_init(&p.writer_ready, NULL);
    p.a = 1;
    p.available = 0;

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, produce_work, &p);
    }
    
    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, consume_work, &p);
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
