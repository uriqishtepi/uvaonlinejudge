#include <stdio.h>
#define HIGH 6227020800ULL
#define LOW  10000


int main()
{
    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        long long int fact = 1;
        while(n > 0) {
            fact *= n;
            --n;
            if(fact > HIGH) { break; }
        }
        if(fact > HIGH) printf("Overflow!\n");
        else if(fact < LOW) printf("Underflow!\n");
        else printf("%lld\n", fact);
    }


    return 0;
}
