#include<stdio.h>
#include<assert.h>
#define debug 0

int ackerman(unsigned long long x)
{
    if(debug) printf("%llu ", x);
    int answ = 0;
    while(x > 1) {
        if(x & 0x1) { /* odd */
            x = 3*x+1;
        }
        else {
            x = x >> 1;
        }
        answ++;
    }
    return answ;
}

int main()
{
    unsigned int a, b;
    while(scanf("%u %u", &a, &b) != EOF && !(a == 0 && b == 0)) {
        long long int i;
        long long int min = a;
        long long int max = b;
        if(a > b) {
            min = b;
            max = a;
        }
        int maxansw = 0;
        unsigned int maxval = 0;
        if(debug) printf("finding Between %lld and %lld\n", min, max);
        for(i = min; i <= max; i++) {
            int answ;
            if(i == 0) answ = 0;
            else if(i == 1) answ = 4;
            else { 
                if(debug) printf("A(%lld) ", i);
                answ = ackerman(i);
                if(debug) printf("{%d}\n", answ);
            }

            /* printf("A(%d): %d\n", i, answ); */
            if(maxansw < answ) {
                maxansw = answ;
                maxval = i;
            }
        }
        printf("Between %u and %u, %u generates the longest sequence of %d values.\n", a, b, maxval, maxansw);
    }

    return 0;
}
