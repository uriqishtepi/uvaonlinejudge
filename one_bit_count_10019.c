#include<stdio.h>

int countBits(int a)
{
    int count = 0;
    while(a > 0) {
        if(a & 0x1) count++;
        a >>= 1;
    }
    return count;
}

int main()
{
    int N;
    int M;
    scanf("%d\n", &N); 
    while(--N >= 0 && scanf("%d\n", &M) != EOF) {
        char buff[10] = {0};
        sprintf(buff, "%d", M);
        int H;
        sscanf(buff, "%x", &H);
        printf("%d ", countBits(M));
        printf("%d\n", countBits(H));
    }

    return 0;
}
