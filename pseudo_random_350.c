#include<stdio.h>
#define MAX 10000

int main()
{
    int Z, I, M, L;
    int casecnt = 0;
    while(scanf("%d %d %d %d", &Z, &I, &M, &L) != EOF && !(Z==0 && I==0 && M == 0 && L==0)) {
        char arr[MAX+1] = {0};
        int count=0;
        for(; arr[L] == 0; L = ((Z*L+I) % M)) {
            arr[L] = count;
            count++;
        }
        /* count-arr[L] we need the length of the cycle */
        printf("Case %d: %d\n", ++casecnt, count-arr[L]);
    }
    return 0;
}
