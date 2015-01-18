#include<stdio.h>
#include<assert.h>
#include<sys/param.h>

int main()
{
    int m=0, n=0;
    while(scanf("%d %d\n", &n, &m) != EOF && !(n ==0 && m == 0)) {
        unsigned long long int res = 1;
        int ni = n;
        int mi = m;
        int nmi = n - m;
        int maxpi = MAX(mi, nmi);
        int minpi = MIN(mi, nmi);
        int siper[200] = {0};
        int poshte[200] = {0};

        int i, j;
        for(i = ni; i > maxpi; i--) siper[i] = i;

        for(i = ni; i > maxpi; i--) {
            for(j = minpi; j > 1; j--) {
                if(poshte[j] == 0 && (siper[i] % j) == 0) {
                    poshte[j] = 1;
                    siper[i] /= j;
                }
            }
        }

        /* after the run all the down slots should be zero */
        for(j = minpi; j > 1; j--) {
            if(poshte[j] != 1) {
                fprintf(stderr, "(%d,%d) can not have split by %d.\n", n, m, j);
            }
            assert(poshte[j] == 1);
        }

        for(i = ni; i > maxpi; i--) {
             res *= siper[i];
        }
        printf("%d things taken %d at a time is %llu exactly.\n", n, m, res);
    }
    return 0;
}
