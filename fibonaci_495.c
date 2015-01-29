#include<stdio.h>

int main()
{
    int F[5001] = {0,1,1};
    int i;
    
    for(i=3;i<=5000;i++) {
        F[i] = F[i-1]+F[i-2];
    }
    int n;
    while(scanf("%d\n", &n) != EOF) {
        printf("The Fibonacci number for %d is %d\n", n, F[n]);
    }
    return 0;
}
