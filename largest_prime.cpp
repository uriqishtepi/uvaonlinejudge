#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include <sys/time.h>
#define forlp(i, a, b, c) for(unsigned long long i = a; i < b; i+=c) 
#define forln(i, a, b, c) for(unsigned long long i = a; i > b; i-=c) 
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ 1000
#define vp std::vector<point> 
#define vui std::vector<unsigned long long> 


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

inline bool isprime(vui & primes, unsigned long long n)
{
    if(n <= 0) return false;
    if(n < 4) return true;
    if((n % 2) == 0) return false;

    for(vui::iterator it = primes.begin(); ((*it) * (*it)) <= n && it != primes.end(); ++it) {
        out("checkin factor %llu\n",*it);
        if((n % (*it)) == 0) return false;
    }
    return true;
}

int mysqrt(unsigned long long n)
{
    //find number s | s * s > n and (s-1)*(s-1) < n
    unsigned int s = n / 2;
    while (s*s > n) {
        s /= 2;
    }
    return s * 2;
}


int main (void)
{
    vui primes; //use this as cache to store the prime numbers seen so far
    primes.push_back(2);
    primes.push_back(3);
    unsigned long long M;
    scanf("%llu\n", &M);

    //get all the primes up to sqrt M
    for(unsigned long long j=5; j*j <= M; j+=2) {
        if(isprime(primes, j)) {
            primes.push_back(j);
            out("adding %llu\n",j);
        }
    }

    if( (M%2)==0) M--;

    //now find largest <= M
    for(unsigned long long i = M; i > 5; i-=2) 
    {
        out("inspecting %llu\n",i);
        if(isprime(primes, i)) {
            printf("%llu\n", i);
            break;
        }
    }
    return 0;
}
