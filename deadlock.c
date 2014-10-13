#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()

struct thrd_param {
    int th;
    int a;
    int b;
    pthread_mutex_t mutex_a;
    pthread_mutex_t mutex_b;
};

typedef struct thrd_param thrd_param;

/* this function tries to get two threads in a deadlock
 * but deadlock is not guaranteed depending on timing, 
 * so needs to be called a bunch of times before it can
 * actually occur */
void * try_deadlock(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int rc;
    if(p->th == 0) {
        rc = pthread_mutex_lock (&p->mutex_a);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        usleep(1);
        rc = pthread_mutex_lock (&p->mutex_b);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        rc = pthread_mutex_unlock (&p->mutex_b);
        rc = pthread_mutex_unlock (&p->mutex_a);
    }
    else {
        rc = pthread_mutex_lock (&p->mutex_b);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        usleep(1);
        rc = pthread_mutex_lock (&p->mutex_a);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        rc = pthread_mutex_unlock (&p->mutex_b);
        rc = pthread_mutex_unlock (&p->mutex_a);
    }
    return NULL;
}

/* deadlock in this case is certain because we wait in each thread
 * until the other one has set it's lock and now is waiting to 
 * get the other lock */
void * certain_deadlock(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int rc;
    if(p->th == 0) {
        rc = pthread_mutex_lock (&p->mutex_a);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        p->a = 1; 
        while(!p->b) //guaranntee that other thread has this lock
            usleep(1);
        rc = pthread_mutex_lock (&p->mutex_b);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        rc = pthread_mutex_unlock (&p->mutex_b);
        rc = pthread_mutex_unlock (&p->mutex_a);
    }
    else {
        rc = pthread_mutex_lock (&p->mutex_b);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        p->b = 1;
        while(!p->a)
            usleep(1);

        rc = pthread_mutex_lock (&p->mutex_a);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        rc = pthread_mutex_unlock (&p->mutex_b);
        rc = pthread_mutex_unlock (&p->mutex_a);
    }
    return NULL;
}




int main()
{
    //call 10 threads to increase variable passed in


    thrd_param p;
    pthread_mutex_init(&p.mutex_a, NULL);
    pthread_mutex_init(&p.mutex_b, NULL);
    pthread_t thv[THREADNUM];
    int i = 0;

    while(1) {
        printf("i=%d\n",i++);
        p.th = 0;
        p.a = 0;
        p.b = 0;
        pthread_create(&thv[0], NULL, certain_deadlock, &p);
        p.th=1;
        pthread_create(&thv[1], NULL, certain_deadlock, &p);
        void *val;
        pthread_join(thv[0], &val);
        pthread_join(thv[1], &val);
    }

    return 0;
}

