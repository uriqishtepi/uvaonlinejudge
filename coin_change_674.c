#include<stdio.h>

#define MAXI 27

int getCount(int n)
{
    int i,j,k,l;
    int count = 0;
    for(i=0; i <= (n/50); i++) {
        for(j=0; j <= (n-i*50) / 25; j++) {
            for(k=0; k <= (n-i*50 - j * 25) / 10; k++) {
                for(l=0; l <= (n-i*50 - j * 25 - k * 10) / 5; l++) {
                    count++;
                    //if (n-i*50 - j * 25 - k * 10 - l * 5 > 0) count++;
                }
            }
        }
        
    }
    return count;
}

int main()
{
    int D[MAXI+1] = {0};
    int i = 0;
printf("%d %d\n", i, getCount(7890));
    for (i = 0; i < MAXI+1; i++) {
    }

    return 0;
}
