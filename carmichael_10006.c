#include<stdio.h>

int isPrime(int pa[], int n)
{
    int i = 0;
    for(i = 0; pa[i] != 0 && pa[i]*pa[i] <= n; i++) {
        int q = n / pa[i];
        if(q * pa[i] == n) return 0;
    }
    return 1;
}


/* compute a ^ n mod n */
int itpowermod(int a, int n)
{
    int i;
    int prod = 1;
    for(i = 0; i < n; i++)
        prod = (prod * a) % n;

    return prod;
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
int powermod(int a, int n)
{
    int bn = n;
    int prod = 1;
    int sq = a;
    do {
        if(bn & 0x1) {
            prod = (prod * sq) % n;
        }
        sq = (sq * sq) % n;
        bn >>= 1;
    } while(bn > 0);

    return prod;
}

/* fermat's test, if number n satisfies:
 *    a ^ n mod n = a 
 * then n is probably prime
 * Charmichael numbers pass fermat's tests for all numbers 1 < a < n
 */
int isCharM(int pa[], int n)
{
    int i = 0;
    for(i = 0; i < n; i++) {
        if(powermod(i, n) != i)
            return 0;
    }
    return 1;
}

#define MX 8000

int find_charms()
{
    int pa[MX] = {0}; /* primes array */
    int pc = 0; /* primes counter */
    pa[pc++] = 2;
    pa[pc++] = 3;
    pa[pc++] = 5;

    int ca[20] = {0}; /* charm array */
    int cc = 0;

    /* find all primes */
    int i;
    for(i = 7; i < 70000 && pc < MX; i+=2) {
        if(isPrime(pa, i)) 
            pa[pc++] = i;
        else if(isCharM(pa, i)) 
            ca[cc++] = i;
    }

    for(i = 0; i < pc; i++)
        printf("%d ", pa[i]);
    printf("\n");

    printf("\nCharms:");
    for(i = 0; i < cc; i++)
        printf("%d ", ca[i]);
    printf("\n");


    return 0;
}

int main() 
{
    int Charms[] = {561,1105,1729,2465,2821,6601,8911,10585,15841,29341,41041};
    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        int i;
        int found = 0;
        for(i = 0; i < sizeof(Charms) / sizeof(int); i++) {
            if(Charms[i] == n) {found = 1; break;}
        }
        if(found) printf("The number %d is a Carmichael number.\n",n);
        else printf("%d is normal.\n",n);
    }
    return 0;
}
