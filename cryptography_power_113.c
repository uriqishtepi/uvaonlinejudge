#include<stdio.h>

//returns a ^ b
long double mypow(long double a, int b)
{
    double res = 1;
    int i;
    for(i = 0; i < b; i++)
        res *= a;
    return res;
}


int main()
{
    int n;
    long double p;
    while(scanf("%d\n%Lf\n", &n, &p) != EOF) {
        printf("%d %Lf\n", n, p);
        int k = 0;
        if(n == 1) {
            printf("%lld\n", (long long int) p);
            continue;
        }
        int max = 1;
        long double pwr;
        while((pwr=mypow(max, n)) < p)
            max += max;
        if(pwr - p < max) {
            printf("%d\n", max);
            continue;
        }
        int  min = 1;
        long double half = p / 2;
        while(min < max) {
            int mid = (max + min ) / 2;
            pwr=mypow(mid, n);
            long double diff = pwr - p;
            printf("min %d mid %d max %d\n", min, mid, max);
            printf("pwr %Lf diff %Lf\n", pwr, diff);
            long double absdiff = diff;
            if(diff < 0) absdiff = -diff;
            if(absdiff < mid) {
                printf("Answ %d\n", max);
                break;
            }
            else if(diff > 0) {
                max = mid;
            }
            else 
                min = mid;
        }
    }
    return 0;
}
