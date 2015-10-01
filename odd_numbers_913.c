#include <stdio.h>


int main() 
{
    int n;
    while(scanf("%d", &n) != EOF && n > 1) {
        unsigned long long int order = (n + 1);
        order = order * order;
        order = order / 4;

        unsigned long long int answer = (2 * order - 3) * 3;
        printf("%lld\n", answer);
    }
    return 0;

}
