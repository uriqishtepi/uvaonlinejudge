#include<stdio.h>

unsigned int max = 100000;

int main()
{
    int N = 10001;
    int arr[10010] = {0};
    arr[0] = 1;
    arr[1] = 1;
    int i;
    long long unsigned int fact = 1;
    unsigned int part = 1;
    for(i = 2; i <= N; i++) {
        fact = fact * i;
        while(fact != 0 && (fact % 10) == 0) fact /= 10;

        part = part * i;
        while( (part != 0 && part % 10) == 0) part /= 10;
        if(part > max) part = part % max;

        arr[i] = (int) (part % 10);
        /* printf("i %d %d fact %llu %d\n", i, arr[i], fact, part); */
    }

    while(scanf("%d", &N) != EOF) {
        printf("%5d -> %d\n", N, arr[N]);
    }
    return 0;
}
