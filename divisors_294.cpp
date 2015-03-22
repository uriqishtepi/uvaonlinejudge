#include<set>
#include<stdio.h>

#define MAXP 35000
#define si std::set<long long int> 

void addAllMults(si & s, int val)
{
    si toAdd;
    toAdd.insert(val);
    for(si::iterator it = s.begin(); it != s.end(); it++) {
        toAdd.insert((*it) * val);
    }

    s.insert(toAdd.begin(), toAdd.end());

}

int main()
{
    int primes[MAXP];
    int fptr = 0;
    primes[fptr++] = 2;
    primes[fptr++] = 3;
    primes[fptr++] = 5;
    primes[fptr++] = 7;

    int j;
    int i;
    for(i = 11; i < MAXP; i+=2) {
        int isPrime = 1;
        for(j = 0; j < fptr; j++) {
            if((i % primes[j]) == 0) {
                isPrime = 0;
                break;
            }
        }
        if(isPrime) primes[fptr++] = i;
    }

    /*
    for(j = 0; j < fptr; j++) printf("%d ", primes[j]);
    printf("\n");
    */

    long long int u, l;
    scanf("%lld", &u);
    while(scanf("%lld %lld\n", &u, &l) != EOF) {
        long long int v;
        int maxcount = 0;
        long long int maxval = 0;
        for(v = u; v <= l; v++) {
            int count = 1;
            si s;
            long long int val = v;
            for(j = 0; j < fptr; j++) {
               int p = primes[j];
               while(val > 1 && (val % p) == 0) {
                   count++;
                   val /= p;
                   addAllMults(s, p);
               }
            }
            /* printf("v %lld -> s.sz %d\n", v, s.size()); */
            if(maxcount < s.size()) {
                maxcount = s.size();
                maxval = v;
            }
        }

        if(u == 1 && l == 1) { maxval = 1; }

        printf("Between %lld and %lld, %lld has a maximum of %d divisors.\n"            , u, l, maxval, maxcount+1);
    }

    return 0;
}
