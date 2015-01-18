#include<stdio.h>

int main()
{
    int b, p, m;
    while(scanf("%d\n%d\n%d\n", &b, &p, &m) != EOF) {
        int res = b % m;
        while(--p > 0) {
            long long int mult = res;
            mult = mult * b;
            res = mult % m;
        }
        printf("res = %d\n", res);
    }

    return 0;
}
