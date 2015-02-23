#include<stdio.h>
#define MAXI 1127


int main()
{
    int i, f, q, d, n, c;
    for (i = 0; i < MAXI+1; i++) {
        int count = 0;
        for(f = 0; f*50 <= i; f++) {
            for(q=0; q*25 <= (i-f*50); q++) {
                for(d=0;d*10 <= (i-f*50-q*25); d++) {
                    for(n=0; n*5 <= (i-f*50-q*25-d*10); n++){
                        c = i - -f*50-q*25 - d*10 - n*5;
                        count++;
/* printf("%d: %d %d %d %d %d %d\n", i, c, n, d, q, f, count); */
                    }
                }
            }
        } 
        printf("%d\n", count);
    }

    return 0;
}
