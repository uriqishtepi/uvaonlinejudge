#include<stdio.h>
#include<assert.h>


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
    int a, b;
    while(scanf("%d %d", &a, &b) != EOF && a != 0 && b != 0) {
        int arr[200] = {1};

        int d = (a - b);
        int mx, mn;
        if(d > b) {
            mx = d;
            mn = b;
        }
        else {
            mx = b;
            mn = d;
        }
        
        int cu = 0;
        int i;
        for(i = a; i > mx; i--) {
            arr[i] = i;
        }
        for(i = mn; i > 1; i--) {
            arr[i] = i;
        }

        int j;
        for(i = mn; i > 1; i--) {
            int val = arr[i];
            for (j = a; j > mx && val > 1; j--) {
                int g = gcd(arr[j], val);
                val /= g;
                arr[j] /= g;
            }
            assert(val == 1);
        }
        unsigned long long tot = 1;
        for (j = a; j > mx; j--) {
            tot *= arr[j];
        }
        printf("%lld\n", tot);
    }
    return 0;
}

