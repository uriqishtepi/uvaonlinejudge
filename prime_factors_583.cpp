#include<stdio.h>
#include<vector>

#define vi std::vector<int>

void print_factors(int N, vi & primes, bool isFirst)
{
    //printf("print_factons %d\n", N);
    if(N < 0) { 
        printf("-1 x ");
        N = -N;
    }

    if(!isFirst) {
        printf(" x ");
    }

    for(vi::iterator it = primes.begin(); it != primes.end() && (*it) * (*it) <= N; ++it) {
        int quotient = N / (*it);
        int rem = N - quotient * (*it);
        if( rem == 0 ) {
            printf("%d", *it);
            if(quotient > 1)
                print_factors(quotient, primes, false);
            return;
        }
    }
    printf("%d", N);
}


inline bool is_prime(vi & primes, int a)
{
    for(vi::iterator it = primes.begin(); it != primes.end() && (*it) * (*it) <= a; ++it) 
    {
        if((a % (*it)) == 0) return false;
    }
    return true;
}

#define MAXN (2 << 16)

int main()
{
    /*find primes up to 2^31 */

    vi primes;
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    for(int i = 7; i < MAXN; i+= 2) {
        if(is_prime(primes, i)) {
            primes.push_back(i);
            printf("add %d\n", i);
        }
    }
    //printf("primes up to %d are %d\n", MAXN, primes.size());

    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        printf("%d = ", n);
        print_factors(n, primes, true); printf("\n");
    }

    return 0;
}
