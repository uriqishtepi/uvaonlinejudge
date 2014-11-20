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

    for(vui::iterator it = primes.begin(); ((*it) * (*it)) <= n; it++) {
        out("considering %u\n",*it);
        if((n % *it) == 0) return false;
    }
    return true;
}

int main (void)
{
    vui primes; //use this as cache to store the prime numbers seen so far
    primes.push_back(2);
    primes.push_back(3);
    unsigned int M;
    scanf("%u\n", &M);
    if( (M%2)==0) M--;

    for(unsigned i = 5; i < M;i+=2) 
    {
        out("inspecting %u\n",i);
        if(isprime(primes, i)) {
            primes.push_back(i);
            out("adding %u\n",i);
        }
    }
    printf("%u\n", primes.back());
    return 0;
}
