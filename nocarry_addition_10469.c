#include<stdio.h>

int main()
{
    unsigned int a=6;
    unsigned int b=9;
    while(scanf("%u %u\n", &a, &b) != EOF) 
    {
        int i;
        unsigned int res = 0;
        for(i = 0; i < 32; i++) {
            res |= ((a ^ b) & 0x1) << i;
            a >>= 1;
            b >>= 1;
        }
        printf("%u\n", res);
    }

    return 0;
}
