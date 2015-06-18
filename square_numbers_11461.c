/* find square numbers between a and b */

#include<stdio.h>
#define MX 100000

int binsrch(int sq[], int low, int hi, int a)
{
    if (low >= hi) return low;

    int mid = (low + hi) / 2;
    if(mid == low || mid == hi) return low;
    if(sq[mid] == a) return mid;
    if(sq[mid] < a) return binsrch(sq, mid, hi, a);
    if(sq[mid] > a) return binsrch(sq, low, mid, a);
}

int main()
{
    int sq[333] = {0};
    int sc = 0;
    int i;
    for(i = 0; i*i <= MX; i++) {
        /* printf("%d: %d\n", i, i*i); */
        sq[sc++] = i*i;
    }

    int a, b;
    while( scanf("%d %d", &a, &b) != EOF && !(a == 0 && b == 0)) {

        int add = 0;
        int l1 = binsrch(sq, 0, sc, a);
        int l2 = binsrch(sq, 0, sc, b);
        if(a == 1) add = 1;
        printf("%d\n", l2-l1 + add);

    }

    return 0;
}
