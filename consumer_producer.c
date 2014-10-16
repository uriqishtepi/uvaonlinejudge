#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

/* get acces to critical section via try lock
 * it's a bit faster than the trylock which spins for a while
 * this function tries to get the lock to a shared resource 
 * telling the producers what work there is to be done
 */
void * try_work(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int a;
    while(1) {
        if(p->a > WORKTOBEDONE) return NULL; //it's ok, p->a doesnt decrement
        int rc = pthread_mutex_trylock(&p->mutex);
        if(rc) {
            continue;
        }

        a = p->a;
        p->a = 0; //set to zero anyway
        pthread_mutex_unlock(&p->mutex);

        if(a > WORKTOBEDONE) return NULL;
        if(a > 0) { //i have work to do
            do_some_work(a);
        }
    }
    return NULL;
}

/* get access to the critical section via lock
 * this function tries to get the lock to a shared resource 
 * telling the producers what work there is to be done
 */
void * lock_work(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int a;
    while(1) {
        if(p->a > WORKTOBEDONE) return NULL; //it's ok, p->a doesnt decrement
        int rc = pthread_mutex_lock(&p->mutex);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }

        a = p->a;
        p->a = 0; //set to zero anyway
        pthread_mutex_unlock(&p->mutex);

        if(a > WORKTOBEDONE) return NULL;
        if(a > 0) { //i have work to do
            do_some_work(a);
        }
    }
    return NULL;
}


void * cond_work(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int a;
    int rc;

    while(1) {
        pthread_mutex_lock(&p->mutex);

        rc = 0;
        while(p->a <= WORKTOBEDONE && p->available < 1 && rc == 0) {
            //printf("Reader wait again tid=%llx, rc = %d\n", THREADID, rc);
            rc = pthread_cond_wait(&p->writer_ready, &p->mutex);
            //printf("Reader woke up from wait tid=%llx, rc = %d\n", THREADID, rc);
        }

        if(p->a > WORKTOBEDONE) { 
            pthread_mutex_unlock(&p->mutex);
            return NULL;
        }
        
        //now we get to do some work
        a = p->a;
        p->available--;

        pthread_cond_signal(&p->reader_ready);
        pthread_mutex_unlock(&p->mutex);

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
    pthread_mutex_init(&p.mutex, NULL);
    pthread_cond_init(&p.reader_ready, NULL);
    pthread_cond_init(&p.writer_ready, NULL);
    p.a = 1;
    p.available = 0;

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, cond_work, &p);
    }
    
    int i = 0;
    while(i <= WORKTOBEDONE) {
        pthread_mutex_lock(&p.mutex);

        int rc = 0;
        while(i <= WORKTOBEDONE && p.available >= 1 && rc == 0 ) 
        {
            //printf("Writer wait again rc = %d\n", rc);
            rc = pthread_cond_wait(&p.reader_ready, &p.mutex);
            //printf("Writer woke up from wait rc = %d\n", rc);
        }

        p.available++;
        p.a = ++i; //this signals that there is work to be done
        pthread_cond_signal(&p.writer_ready);
        rc = pthread_mutex_unlock(&p.mutex);
        if(rc) {
            printf("Print error from pthread_mutex_unlock rc = %d\n", rc);
            exit(1);
        }
    }

    pthread_mutex_lock(&p.mutex);
    pthread_cond_broadcast(&p.writer_ready);
    pthread_mutex_unlock(&p.mutex);

    FORL(j, 0, THREADNUM) {
        void *val;
        pthread_join(thv[j], &val);
    }
    return 0;
}

void do_some_work(int a)
{
    printf("Doing Work tid=%llx a=%d\n", THREADID, a);
    usleep(1000*500);
}
