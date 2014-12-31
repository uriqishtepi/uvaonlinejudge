#include<stdio.h>
#include<math.h>


int main()
{
    int n;
    double p;
    while(scanf("%d\n%lf\n", &n, &p) != EOF) {
        /* printf("%d %lf\n", n, p); */
        if(n == 1) {
            printf("%lld\n", (long long int) p);
            continue;
        }
        double k = 0;
        k = log(p);
        k =  k/n;
        k = exp(k);
        printf("%.0lf\n", k);
    }
    return 0;
}
