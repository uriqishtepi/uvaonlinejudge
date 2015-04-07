#include<stdio.h>


int main()
{
    int N;
    while(scanf("%d", &N) != EOF) {
        int i;
        int d = 1;
        for(i = 2; i <= N; i++) {
            d = d * i;
            int rem;
            while( 0 == (rem = d % 10) ) {
                d = d / 10;
            }
            d = rem;
        }
        printf("%5d -> %d\n", N, d);
    }
    return 0;
}
