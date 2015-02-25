#include<stdio.h>
#define MAXL 10000

int main()
{
    int A[MAXL + 2] = {0};
    int l, r, h, i;

    while(scanf("%d %d %d\n", &l, &h, &r) != EOF) {
        for(i = l; i < r; i++) {
            if(A[i] < h) A[i] = h;
        }
    }
    int prev = 0;
    int first = 1;
    for(i = 0; i < MAXL; i++) {
        if(A[i] != prev) { 
            if(!first) printf(" ");
            first=0;
            printf("%d %d", i, A[i]);
            prev = A[i];
        }
    }
    printf("\n");
    return 0;
}
