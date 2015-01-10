#include<stdio.h>


int main()
{
    int n;
    while(scanf("%u\n", &n) != EOF && n >= 0) {
        int i;
        long long unsigned int slices = 1;
        for(i = 1; i <= n; i++) {
            slices += i;
/* printf("%d %d\n", i, slices);             */
        }
        printf("%llu\n", slices);            
    }

    return 0;
}   
