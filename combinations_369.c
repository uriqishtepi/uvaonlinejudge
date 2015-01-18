#include<stdio.h>
#include<assert.h>
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
        int arr[100] = {0};
        int minpicount = 0;
        int loopcount = 0;

        while(ni > maxpi) {
            loopcount++;
            while(res < (1ULL<<63) && ni > maxpi){
                res *= ni;
                ni--;
            }
            minpicount = 1;
            int i = minpi;
            while(i > 1) {  
                if(arr[i] == 0 && (res % i) == 0) {
                    res /= i;
                    arr[i] = 1;
                    printf("working with %llu / %d\n", res, i);
                }
                else if((res % i)) {
                    printf("problem with %llu / %d\n", res, i);
                }
                if(arr[i] == 1) { printf("done with %d \n", i); minpicount++; }
                i--;
            }
        }
        printf("%d things taken %d at a time is %llu exactly.\n", n, m, res);
        if(minpicount != minpi) printf("problem minpicount %d minpi %d loopcount %d\n", minpicount, minpi, loopcount);
    }
    return 0;
}
