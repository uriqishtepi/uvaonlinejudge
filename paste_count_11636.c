#include<stdio.h>

int main()
{

    int N;
    int count = 0;
    while(scanf("%d", &N) != EOF && N > 0) {
        count++;
        int val = 1;
        int i;
        for(i = 0; i < 30 && val < N; i++, val <<=1) { }
        printf("Case %d: %d\n", count, i);
    }

    return 0;
}
