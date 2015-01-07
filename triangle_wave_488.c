#include<stdio.h>

int main ()
{

    int N;
    scanf("%d", &N);

    while(N > 0) { 
        N--;
        int amp = 3;
        int freq = 2;
        scanf("%d %d", &amp, &freq);

        int i;
        int j;
        int k;
        for(i = 0; i < freq; i++) {
            for(j = 1; j < amp; j++) {
                for(k = 1; k <= j; k++) { printf("%d", j); }
                printf("\n");
            }
            for(; j > 0; j--) {
                for(k = 1; k <= j; k++) { printf("%d", j); }
                printf("\n");
            }
            if(i == freq - 1 && N == 0) /* dont print eol for last input */
                continue;
            printf("\n");
        }
    }

    return 0;
}
