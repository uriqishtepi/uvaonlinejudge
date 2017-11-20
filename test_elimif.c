#include<stdio.h>

/* there is no advantage to beat the if stmt 
 * valgrind and timing info show that it is faster with the if */


int main()
{
    int count = 0;
    int oldcount = 2;
    int nretries = 2;
    volatile int increment = 0;
    int i;
    #define MAX 20000000

    for(i = 0; i < MAX; i++) {
        count = (-increment) & oldcount; 
        count += nretries;
    }

    for(i = 0; i < MAX; i++) {
        if (increment) 
            count += nretries;
        else           
            count = nretries; 
    }

    for(i = 0; i < MAX; i++) {
        count = increment * oldcount; 
        count += nretries;
    }
    printf("count %d\n", count);
    printf("__DBL_MAX_10_EXP__ %d\n", __DBL_MAX_10_EXP__);

    return 0;
}
