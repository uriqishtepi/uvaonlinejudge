#include<stdio.h>
#include<assert.h>
#include<limits.h>
#define debug 0

/*
 * ex...6 steps for 10
 * 10 5 16 8 4 2 1
 * issue here is that x can go up and down and it may go beyond long long?
 *
 */

int ackerman(unsigned long long x)
{
    if(debug) printf("%llu ", x);
    long long int threshold = (ULONG_MAX - 1) / 3;
    int answ = 0;
    while(x > 1) {
        assert(x < threshold); /* should stop from wrapping around */
        long long isOdd = x & 0x1;
        long long mIsOdd = -isOdd;
        long long nex = (mIsOdd & (3*x+1) ) | ((~mIsOdd) & (x>>1));
        /*
        printf("x %lld\n", x);
        printf("isodd %lld\n", isOdd);
        printf("misodd %lld\n", mIsOdd);
        printf("(mIsOdd | (3*x+1) ) %lld\n", (mIsOdd & (3*x+1) ));


        if(x & 0x1) { 
            x = 3*x+1;
        }
        else {
            x = x >> 1;
        }
        printf("nex %lld vs x %llu\n", nex, x);
        */
        x = nex;
        answ++;
    }
    return answ;
}


int main()
{
    unsigned int a, b;
    while(scanf("%u %u", &a, &b) != EOF && !(a == 0 && b == 0)) {
        long long int i;
        long long int L = a;
        long long int H = b;
        if(a > b) {
            L = b;
            H = a;
        }
        assert(L <= H);
        int S = 0;
        long long int V = 0;
        if(debug) printf("finding Between %lld and %lld\n", L, H);
        for(i = L; i <= H; i++) {
            int answ;
            if(i == 0) answ = 0;
            else if(i == 1) answ = 4;
            else { 
                if(debug) printf("A(%lld) ", i);
                answ = ackerman(i);
                if(debug) printf("{%d}\n", answ);
            }

            /* printf("A(%d): %d\n", i, answ); */
            if(S < answ) {
                S = answ;
                V = i;
            }
        }
        printf("Between %lld and %lld, %lld generates the longest sequence of %d values.\n", L, H, V, S);
    }

    return 0;
}
