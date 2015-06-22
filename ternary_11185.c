#include<stdio.h>


int main()
{
    int N;
    while(scanf("%d", &N) != EOF && N != -1) {
        char tn[33] = {0};
        int i = 31;
        if(N == 0) { printf("0\n"); continue; }

        while(N > 0) {
            int q = N / 3;
            int rem = N - (q*3);
            tn[i] = rem + '0';
            i--;
            N = q;
        }
        printf("%s\n", &tn[i+1]);
    }
}
