#include<stdio.h>
#define MAXI 127


int main()
{
    int D[MAXI+1] = {0};
    int i = 0;
    int c5 = -1;
    int c10 = -1;
    int c25 = -1;
    int c50 = -1;
    int count = 1;
    for (i = 0; i < MAXI+1; i++) {
        if(++c5 == 5) { c5=0; count++; }
        if(++c10 == 10) { c10=0; count++; }
        if(++c25 == 25) { c25=0; count++; }
        if(++c50 == 50) { c50=0; count++; }
        printf("%d %d %d %d %d %d\n", i, c5, c10, c25, c50, count);
    }

    return 0;
}
