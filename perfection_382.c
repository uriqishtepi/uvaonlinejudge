#include<stdio.h>

int main()
{
    int n;
    printf("PERFECTION OUTPUT\n");
    while(scanf("%d",&n) != EOF && n != 0) {
        int i;
        int sum = 1;
        for(i=2;i<=n/2 + 1;i++) {
            if(n % i == 0) {
                /* printf("%d divides %d\n", i, n); */
                sum += i;
            }
        }
        printf("%5d ", n);
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
