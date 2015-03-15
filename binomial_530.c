#include<stdio.h>
#include<assert.h>


long long int gcd(long long int a, long long int b)
{
    if(a == 0) return b;
    if(b == 0) return a;
    if(a == 1 || b == 1) return 1;

    long long int mi = a, ma = b;
    if(a > b) {
        mi = b;
        ma = a;
    }

    return gcd (ma % mi, mi);
}


/* ( a )
 * ( b )  = a! / (b! * (a - b)!
 *
 * 4,2  = 4*3*2/(2 * 2) = 3*2
 *
 *
 * a,b
 *
 * 46,6
 * mx = 40
 * mn  = 6
 */
int main()
{
    long long int a, b;
    while(scanf("%lld %lld", &a, &b) != EOF && !(a == 0 && b == 0)) {
        int arr[200] = {1};
        assert(a >= b);
        long long int up[2000] = {0};
        long long int down[2000] = {0};

        long long int d = (a - b);
        long long int mx, mn;
        if(d > b) {
            mx = d;
            mn = b;
        }
        else {
            mx = b;
            mn = d;
        }
        
        int cu = 0;
        int cd = 0;
        int i;
        for(i = a; i > mx; i--) {
            up[cu++] = i;
        }
        for(i = mn; i > 1; i--) {
            down[cd++] = i;
        }

        int j;
        for(i = 0; i < cd; i++) {
            long long int dval = down[i];
            for (j = 0; j < cu && dval > 1; j++) {
                long long int g = gcd(up[j], dval);
                dval /= g;
                up[j] /= g;
            }
            assert(dval == 1);
        }
        unsigned long long tot = 1;
        for (j = 0; j < cu; j++) {
            tot *= up[j];
        }
        printf("%lld\n", tot);
    }
    return 0;
}

