#include<stdio.h>

int main()
{
    int n;
    int i = 1;
    scanf("%d", &n);
    while(i <= n){
        int N, K, P;
        scanf("%d %d %d", &N, &K, &P);
        int out = (K+P)%N;
        if (out == 0) out = N;
        printf("Case %d: %d\n", i, out);
        i++;
    }

    return 0;
}
