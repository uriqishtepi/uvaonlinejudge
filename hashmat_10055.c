#include <stdio.h>


int main ()
{
    long long int a, b;
    int counter = 0;
    while(scanf("%lld %lld\n", &a, &b) != EOF) {
        long long int d = a > b ? a-b : b-a;
        printf("%lld\n", d);
    }
    return 0;
}
