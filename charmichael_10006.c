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
int powermod(int a, int n)
{
    int i;
    int prod = 1;
    for(i = 0; i < n; i++)
        prod = (prod * a) % n;

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

#define MX 2000

int main()
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
    for(i = 7; i < 6000 && pc < MX; i+=2) {
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
