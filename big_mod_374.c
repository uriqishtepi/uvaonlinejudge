#include<stdio.h>

int main()
{
    int b, p, m;
    while(scanf("%d\n%d\n%d\n", &b, &p, &m) != EOF) {
        int res = 1; 
        int ap = b % m;
        int power = 1;
        while(power <= p && power > 0) {
            if(power & p) {
                res = (res * ap) % m;
            }
            ap = (ap * ap) % m;
            power <<= 1;
        }
        printf("%d\n", res);
    }

    return 0;
}
