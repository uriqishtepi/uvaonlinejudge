#include<stdio.h>
#include<sys/param.h>

int main()
{
    int m=0, n=0;
    while(scanf("%d %d\n", &n, &m) != EOF && n !=0 && m != 0) {
        unsigned long long int res = 1;
        int ni = n;
        int mi = m;
        int nmi = n - m;
        int maxpi = MAX(mi, nmi);
        int minpi = MIN(mi, nmi);

        while(ni > maxpi) {
            while(res < (1ULL<<63) && ni > maxpi){
                res *= ni;
                ni--;
            }
            while(minpi > 1 && (res % minpi) == 0) {
                res /= minpi;
                minpi--;
            }
        }
        printf("%d things taken %d at a time is %llu exactly.\n", n, m, res);
    }
    return 0;
}
