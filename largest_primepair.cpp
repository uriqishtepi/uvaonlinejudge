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

inline bool isprime(unsigned int n)
{
    if(n <= 0) return false;
    if(n < 4) return true;
    if((n % 2) == 0) return false;

    forlp(i, 3, n, 2) {
        //printf("considering %d\n",i);
        if((n % i) == 0) return false;
    }
    return true;
}

int main (void)
{
    unsigned int M;
    scanf("%u\n", &M);
    bool two_ahead = false;
    if( (M%2) == 0) M--; //only look at even
    forln(i,M,1,2) {
        printf("investigating %d\n",i);
        bool curr = isprime(i);
        if(curr && two_ahead) {
            printf("%d %d\n",i,i+2);
            break;
        }
        two_ahead = curr;
    }
    return 0;
}
