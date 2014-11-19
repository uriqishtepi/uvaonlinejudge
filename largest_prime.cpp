#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include <sys/time.h>
#define forlp(i, a, b, c) for(int i = a; i < b; i+=c) 
#define forln(i, a, b, c) for(int i = a; i > b; i-=c) 
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ 1000
#define vp std::vector<point> 


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

bool isprime(int n)
{
    if(n <= 0) return false;
    if(n < 4) return true;

    forln(i, n-1, 1, 1) {
        printf("considering %d\n",i);
        if((n % i) == 0)
            return false;
    }
    return true;

}

int main (void)
{
    int M;
    scanf("%d\n", &M);
    forlp(i,0,M,1) {
        if(isprime(i))
            printf("%d\n",i);
    }
    return 0;
}
