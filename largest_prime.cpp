#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include <sys/time.h>
#define forlp(i, a, b, c) for(unsigned int i = a; i < b; i+=c) 
#define forln(i, a, b, c) for(unsigned int i = a; i > b; i-=c) 
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ 1000
#define vp std::vector<point> 
#define vui std::vector<unsigned int> 


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

inline bool isprime(vui & primes, unsigned int n)
{
    if(n <= 0) return false;
    if(n < 4) return true;
    if((n % 2) == 0) return false;

    for(vui::iterator it = primes.begin(); ((*it) * (*it)) <= n && it != primes.end(); ++it) {
        out("checkin factor %u\n",*it);
        if((n % (*it)) == 0) return false;
    }
    return true;
}

int mysqrt(unsigned int n)
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
    unsigned int M;
    scanf("%u\n", &M);

    if( (M%2)==0) M--;

    //found i, sqrt M, now get all the primes up to i
    for(unsigned int j=5; j*j <= M; j+=2) {
        if(isprime(primes, j)) {
            primes.push_back(j);
            out("adding %u\n",j);
        }
    }

    //now find largest <= M
    for(unsigned i = M; i > 5; i-=2) 
    {
        out("inspecting %u\n",i);
        if(isprime(primes, i)) {
            printf("%u\n", i);
            break;
        }
    }
    return 0;
}
