/* This example shows the timings of using different atomic primitives 
 * with respect to no locking, mutex locking, rwlocking.
 * It seems that __atomic_add_fetch is only twice as slow as no atomics
 * and cmpxch is four times cheaper than mutex, here is from my laptop:
 *
       adding inline diff =        59504usec
            function diff =       129602usec
               mutex diff =       876026usec
              rdlock diff =      1147439usec
              rwlock diff =      1069807usec
     atomic addfetch diff =       128197usec
     atomic cmpxchng diff =       223013usec
       sync cmpxchng diff =       208053usec

 *
 * to compile use  cc -lpthread  -o compare_atomics compare_atomics.c
 * */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define FORL(ii,s,e) for(int ii = s; ii < e; ii++)
#define THREADNUM 10
#define THREADID (long long unsigned int) pthread_self()
#define WORKTOBEDONE 100
#define BIGNUM 1<<24
#define QMAX 20


void timediff(const char * s) {
    static struct timeval tv;
    struct timeval tmp;

    gettimeofday(&tmp, NULL);
    int sec = (tmp.tv_sec - tv.tv_sec)*1000000;
    int msec = (tmp.tv_usec - tv.tv_usec);
    printf("%20.20s diff = %12.dusec\n", s, sec + msec);
    tv = tmp;
}

void addThree(int * l)
{
    *l += 3;
}


int main()
{
    struct timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

    //call 10 threads to do some work 
    int s = 0;
    int l = 0;
    timediff("start");
    s = 0;
    FORL(i, 0, BIGNUM) {
        s += 3;
    }
    timediff("adding inline");

    l = 0;
    FORL(i, 0, BIGNUM) {
        addThree(&l);
    }
    assert(l == s);
    timediff("function");

    l = 0;
    FORL(i, 0, BIGNUM) {
        pthread_mutex_lock(&mutex);
        l += 3;
        pthread_mutex_unlock(&mutex);
    }
    assert(l == s);
    timediff("mutex");

    l = 0;
    FORL(i, 0, BIGNUM) {
        pthread_rwlock_rdlock(&lock);
        l += 3;
        pthread_rwlock_unlock(&lock);
    }
    assert(l == s);
    timediff("rdlock");

    l = 0;
    FORL(i, 0, BIGNUM) {
        pthread_rwlock_wrlock(&lock);
        l += 3;
        pthread_rwlock_unlock(&lock);
    }
    assert(l == s);
    timediff("rwlock");

    l = 0;
    FORL(i, 0, BIGNUM) {
        __atomic_add_fetch(&l, 3, __ATOMIC_SEQ_CST);
    }
    assert(l == s);
    timediff("atomic addfetch");

    l = 0;
    FORL(i, 0, BIGNUM) {
        int old;
        int new;
        do {
            old = l;
            new = l + 3;
        } while(!__atomic_compare_exchange(&l, &old, &new, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
    }
    assert(l == s);
    timediff("atomic cmpxchng");

    l = 0;
    FORL(i, 0, BIGNUM) {
        int old;
        int new;
        do {
            old = l;
            new = l + 3;
        } while(!__sync_bool_compare_and_swap(&l, old, new));
    }
    assert(l == s);
    timediff("sync cmpxchng");

    printf("l=%d\n",l);
    
    return 0;
}

void do_some_work(int a)
{
    //printf("Doing Work tid=%llx a=%d\n", THREADID, a);
    //usleep(1000*500);
}
