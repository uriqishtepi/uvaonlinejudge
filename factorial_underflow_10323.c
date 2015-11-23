#include <stdio.h>
#define HIGH 6227020800ULL
#define LOW  10000


int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n <= 0) { /* absurd computing of factorial of negative */
            if(n & 0x1 ) printf("Overflow!\n");
            else printf("Underflow!\n");
            continue;
        }
        long long int fact = 1;
        while(n > 1) {
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
