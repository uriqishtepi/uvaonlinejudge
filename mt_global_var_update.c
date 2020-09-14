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

int avg;
typedef struct thrd_param thrd_param;

void * try_race(void *arg)
{
    int i = 0;
    while(i++ < 10000000) {
        int a = rand()%100;
        avg += (a - avg) >> 4;
        if (avg > 20000)
            avg = 20000;
    }
    return NULL;
}

void * less_race(void *arg)
{
    int i = 0;
    while(i++ < 10000000) {
        int a = rand()%100;
        int loc = avg;
        loc += (a - loc) >> 4;
        if (loc > 20000)
            loc = 20000;
        avg = loc;
    }
    return NULL;
}


int main()
{
    //call 10 threads to increase variable passed in

    thrd_param p;
    p.a = 0;
    pthread_t thv[THREADNUM];

    FORL(i, 0, THREADNUM) {
        pthread_create(&thv[i], NULL, try_race, &p);
        //pthread_create(&thv[i], NULL, less_race, &p);
    }

    FORL(i, 0, THREADNUM) {
        void *val;
        pthread_join(thv[i], &val);
    }
    printf("avg = %d\n", avg);
    return 0;
}

