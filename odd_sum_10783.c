#include<stdio.h>
int main()
{
    unsigned int a, b;
    int n;
    scanf("%d\n",&n);
    int ncount = 0;
    while(scanf("%u %u\n", &a, &b) != EOF) {
        a = (a/2) * 2 + 1;
        b = ((b+1)/2) * 2;
        int sum = (b-a+1)*(b+a-1)/2;
        printf("Case %d: %d\n", ++ncount, sum/2);
    }

    return 0;
}
