#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100

struct thrd_param {
    int a;
    pthread_mutex_t mutex;
};

typedef struct thrd_param thrd_param;

/* this function tries to get the lock to a shared resource 
 * telling the producers what work there is to be done
 */
void * try_work(void *arg)
{
    thrd_param *p = (thrd_param *) arg;
    int a;
    while(1) {
        if(p->a >= WORKTOBEDONE) return NULL; //it's ok, p->a doesnt decrement
        int rc = pthread_mutex_trylock(&p->mutex);
        if(rc) {
            continue;
        }

        a = p->a;
        p->a = 0; //set to zero anyway
        pthread_mutex_unlock(&p->mutex);

        if(a > WORKTOBEDONE) return NULL;
        if(a > 0) { //i have work to do
            //do work
            printf("Doing Work tid=%llx a=%d\n", THREADID, a);
            usleep(1000*500);
        }
    }
    return NULL;
}




int main()
{
    //call 10 threads to increase variable passed in


    thrd_param p;
    p.a = 1;
    pthread_mutex_init(&p.mutex, NULL);
    pthread_t thv[THREADNUM];

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, try_work, &p);
    }
    
    int i = 0;
    while(i < WORKTOBEDONE+1) {
        int rc = pthread_mutex_lock(&p.mutex);
        if(rc) {
            printf("Print error from pthread_mutex_lock rc = %d\n", rc);
            exit(1);
        }
        if(p.a == 0)
            p.a = i++; //this signals that there is work to be done
        
        rc = pthread_mutex_unlock (&p.mutex);
        if(rc) {
            printf("Print error from pthread_mutex_unlock rc = %d\n", rc);
            exit(1);
        }
    }

    FORL(j, 0, THREADNUM) {
        void *val;
        pthread_join(thv[j], &val);
    }
    return 0;
}

