#include<stdio.h>

/* compute a ^ n mod n */
int itpowermod(int b, int e, int m)
{
    int i;
    long long int prod = 1;
    for(i = 0; i < e; i++) {
        prod = prod * b;
        prod = prod % m;
    }

    return (int) prod;
}


/* compute a ^ n mod n 
 *
 * a ^ 3 = a^2 * a
 * a ^ 4 = a^4
 * a ^ 7 = a^4 * a^2 * a
 *
 * 9 => 1001 :  2^9 = 2^8 * 2
 *
 * 2^2 % 9 =  4 % 9 = 4
 * 2^4 % 9 = 16 % 9 = 7
 * 2^8 % 9 =256 % 9 = 4 
 * 7 * 7   = 49 % 9 = 4
 *
 * a=2 n=9 bn=9 sq=2 prod=2
 * a=2 n=9 bn=4 sq=4 prod=2
 * a=2 n=9 bn=2 sq=7 prod=2
 * a=2 n=9 bn=1 sq=4 prod=4
 * a=2 n=9 bn=0 sq=7 prod=4 itpw=8
 *
 */
int binpowermod(int b, int e, int m)
{
    int bn = e;
    long long int prod = 1;
    long long int sq = b % m;
    do {
        if(bn & 0x1) {
            prod = (prod * sq) % m;
        }
        sq = (sq * sq) % m;
        bn >>= 1;
    } while(bn > 0);

    return (int) prod;
}



int main() 
{
    int b,e,m;/*base, exp, modulus */
    while(scanf("%d %d %d", &b, &e, &m) != EOF ) {
        int res;
        if(0== m) {res=-1; continue;}
        if(0 == b) res = 0;
        else if (0 == e) res = 1;
        printf("%d^%d (mod %d) is %d\n", b, e, m, binpowermod(b,e,m));
    }
    return 0;
}
