#include <stdio.h>

int main()
{
    int num;
    while(scanf("%d", &num) != EOF && num > 0) {
        int parity = 0;
        char str[65] = {0};
        int i = 0;
        while(num > 0) {
            char bit = num & 0x1;
            parity += bit;
            str[i] = bit; 
            num >>= 1;
            i++;
        }
        printf("The parity of ");
        while(i>0) {
            i--;
            printf("%c", str[i]+'0');
        }
        printf(" is %d (mod 2).\n", parity);
    }

    return 0;
}
