#include<stdio.h>

int main()
{
    int n;
    printf("PERFECTION OUTPUT\n");
    while(scanf("%d",&n) != EOF && n != 0) {
        printf("%5d  ", n);
        if(n == 1) {
            printf("DEFICIENT\n");
            continue;
        }
        int i;
        int sum = 1;
        for(i=2;i <= n/2; i++) {
            if(n % i == 0) {
                /* printf("%d divides %d, sum = %d\n", i, n, sum); */
                sum += i;
            }
        }
        if(sum > n)
            printf("ABUNDANT\n");
        else if(sum < n)
            printf("DEFICIENT\n");
        else
            printf("PERFECT\n");
    }
    printf("END OF OUTPUT\n");

    return 0;
}
