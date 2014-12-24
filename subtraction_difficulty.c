#include<stdio.h>
int main()
{
    long long int a, b;
    int ncount = 0;
    while(scanf("%llu %llu\n", &a, &b) != EOF && (a != 0 || b != 0)) {
        int borrow = 0;
        int count = 0;
        while(a > 0 || b > 0) {
            unsigned int ap = (a % 10);
            unsigned int bp = (b % 10);
            if(ap < bp + borrow) {
                count++;
                borrow = 1;
            }
            else borrow = 0;
            a /= 10;
            b /= 10;
        }
        /* if(ncount++ > 0) printf("\n"); */
        if(count>1) 
            printf("%d carry operations.", count);
        else if(count==1) 
            printf("1 carry operation.");
        else
            printf("No carry operation.");
        printf("\n"); 
    }

    return 0;
}
