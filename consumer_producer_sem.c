/* this example emulates multiple consumer one producer 
 * which coordinate via samaphore
 */
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100

int done = 0;
struct thrd_param {
    int a;
    int available;
    sem_t produce_more;
    sem_t consume_more;
};

typedef struct thrd_param thrd_param;
void do_some_work(int);

/* use conditional variables and mutex to get the producer and 
 * consumer to coordinate
 */
void * sem_work(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int a;
    int rc;

    while(!done) {
        rc = sem_wait(&p->produce_more);
        if(rc) {
            printf("Print error from sem_wait rc = %d\n", rc);
            exit(1);
        }
        //printf("C Consuming... tid=%llx p.a=%d\n", THREADID, p->a);
        
        //now we get to do some work
        a = p->a;
        p->available--;

        rc = sem_post(&p->consume_more);
        if(rc) {
            printf("Print error from sem_post rc = %d\n", rc);
            exit(1);
        }

        if(a > 0) { //i have work to do
            do_some_work(a);
        }
    }
    return NULL;
}

int main()
{
    //call 10 threads to do some work 
    pthread_t thv[THREADNUM];
    thrd_param p;
    sem_init(&p.produce_more, 0, 0);
    sem_init(&p.consume_more, 0, 1);
    p.a = 1;
    p.available = 0;

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, sem_work, &p);
    }
    
    int rc;
    int i = 0;
    while(!done) {
        rc = sem_wait(&p.consume_more);
        if(rc) {
            printf("Print error from sem_wait rc = %d\n", rc);
            exit(1);
        }

        p.available++;
        p.a = ++i; //this signals that there is work to be done
        if(i > WORKTOBEDONE) { 
            done = 1;
        }
        //printf("P Posting... tid=%llx p.a=%d\n", THREADID, p.a);
        rc = sem_post(&p.produce_more);
        if(rc) {
            printf("Print error from sem_post rc = %d\n", rc);
            exit(1);
        }
    }

    FORL(j, 0, THREADNUM) {
        void *val;
        pthread_join(thv[j], &val);
    }
    sem_destroy(&p.produce_more);
    sem_destroy(&p.consume_more);
    return 0;
}

void do_some_work(int a)
{
    usleep(1000*500);
    printf("Doing Work tid=%llx a=%d\n", THREADID, a);
}
