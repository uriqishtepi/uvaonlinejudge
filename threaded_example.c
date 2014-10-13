#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()

struct thrd_param {
    int a;
    pthread_mutex_t mutex;
};

typedef struct thrd_param thrd_param;

/* this function tries to get the various threads in a race
 * by updating a shared variable and checking that it was updated
 * correctly. It takes several thousand iterations before we can 
 * catch a differnt thread updating p->a while we were not looking.
 */
void * try_race(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    while(1) {
        int a = p->a;
        p->a++;
        if(a != p->a-1) {
            printf("Print param tid=%llx a=%d\n", THREADID, p->a);
            exit(1);
        }
    }
    return NULL;
}


void * lock_no_race(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    while(1) {
      {
        int rc = pthread_mutex_lock (&p->mutex);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        int a = p->a;
        p->a++;
        if(a != p->a-1) {
            printf("Print param tid=%llx a=%d\n", THREADID, p->a);
            exit(1);
        }
        rc = pthread_mutex_unlock (&p->mutex);
        if(rc) {
            printf("Print error from pthread_mutex_unlock rc = %d\n", rc);
            exit(1);
        }
      }
    }
    return NULL;
}


int main()
{
    //call 10 threads to increase variable passed in


    thrd_param p;
    p.a = 0;
    pthread_mutex_init(&p.mutex, NULL);
    pthread_t thv[THREADNUM];

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, lock_no_race, &p);
    }

    FORL(i, 0, THREADNUM) {
        void *val;
        pthread_join(thv[i], &val);
    }
    return 0;
}

