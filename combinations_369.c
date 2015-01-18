#include<stdio.h>
#include<assert.h>
#include<sys/param.h>

int gcd(int a, int b)
{
    if(a == 0) return b;
    if(b == 0) return a;
    if(a == 1 || b == 1) return 1;

    int mi = a, ma = b;
    if(a > b) {
        mi = b;
        ma = a;
    }

    int frac = ma / mi;
    return gcd (ma - mi*frac, mi);
}

int main()
{
    /*
    printf("test gcd 4,6 = %d\n", gcd(4,6));
    printf("test gcd 6,4 = %d\n", gcd(6,4));
    printf("test gcd 10,3 = %d\n", gcd(10,3));
    printf("test gcd 3,3 = %d\n", gcd(3,3));
    printf("test gcd 6,3 = %d\n", gcd(6,3)); */
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
        for(j = minpi; j > 1; j--) poshte[j] = j;

        for(i = ni; i > maxpi; i--) {
            for(j = minpi; j > 1; j--) {
                if(poshte[j] == 0)
                    continue;
                int part = gcd(siper[i], poshte[j]);
                if(part != 1) {
                    poshte[j] /= part;
                    siper[i] /= part;
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
