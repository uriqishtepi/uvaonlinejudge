#include<stdio.h>
#define MAXI 500


int main()
{
    int D[MAXI + 1];
    int i, f, q, d, n, c;
    for (i = 0; i < MAXI+1; i++) {
        int count = 0;
        int N = i * 5;
        for(f = 0; f*50 <= N; f++) {
            for(q=0; q*25 <= (N-f*50); q++) {
                for(d=0;d*10 <= (N-f*50-q*25); d++) {
                    for(n=0; n*5 <= (N-f*50-q*25-d*10); n++){
                        c = N - f*50-q*25 - d*10 - n*5;
                        count++;
                        D[i] = count;
 /* printf("%d: %d %d %d %d %d %d\n", i, c, n, d, q, f, count); */
                    }
                }
            }
        } 
    }

    int p;
    while(scanf("%d\n", &p) != EOF) {
        printf("%d\n", D[p/5]);
    }

    return 0;
}
