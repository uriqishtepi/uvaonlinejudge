#include<stdio.h>
#include<assert.h>

int main()
{
    int agecount[101] = {0};
    int t;
    int n;
    while(scanf("%d\n", &t) != EOF && t != 0) {
        while(--t >= 0 && scanf("%d ", &n) != EOF) {
            assert(n > 0 && n < 100);
            agecount[n]++;
        }

        int count = 0;
        for(n=1;n<100;n++) {
            while(agecount[n] > 0) {
                if(count++ != 0) printf(" ");
                printf("%d", n);
                agecount[n]--;
            }
        }
        printf("\n");
    }

    return 0;
}
