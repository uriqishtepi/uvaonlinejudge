#include<stdio.h>

#define MAXI 7489

int main()
{
    int i;
    int D[MAXI+1] = {0};
    for (i = 0; i < MAXI+1; i++) {
        D[i] += 1;
        if(i >= 5) 
            D[i] += D[i - 5];
        if(i >= 10)
            D[i] += D[i - 10];
        if(i >= 25)
            D[i] += D[i - 25];
        if(i >= 50)
            D[i] += D[i - 50];

printf("%d %d\n", i, D[i]);
    }

    return 0;
}
