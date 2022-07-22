#include <stdio.h>
#include <math.h>
#include <limits.h>

//#define out printf
#define out


/* binsearch to root */
unsigned long long int mysqrt(unsigned long long int num)
{
    unsigned long long int a = 0;
    unsigned long long int b = num;
    if (num <= 1) return num;
    if (num == 2) return 1;

    while (1) {
        unsigned long long int mid = (a + b)/2;
        if (mid > UINT_MAX) mid = UINT_MAX - 1;

        if(mid * mid <= num) {
            unsigned long long int mid_p = mid+1;
            if (mid_p * mid_p > num)
                return mid;
            a = mid; 
        } else 
            b = mid;
    }
}

int main() 
{
    int n;
    /*
    for(int i=0; i <= 100; i++)
        printf("%d %d\n", i, mysqrt(i));
        */

    scanf("%d", &n);
    while (n--) {
        //quadratic_solution [-b +- sqrt(b^2 - 4ac) ]/ 2a
        //x^2+x-2k=0 => x= [-1 +- sqrt(1+4*2k) ] / 2
        //will this mult overflow double?
        unsigned long long int k; // = 952921504606846974LL;
        scanf("%lld", &k);
        unsigned long long int sol = (mysqrt(1+4*2*k) - 1) / 2;
        //out("k=%lld sol=%lld\n", k, sol);
        printf("%lld\n", sol);
    }

    return 0;
}
