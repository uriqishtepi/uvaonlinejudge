#include<vector>
#include<algorithm>
#include<stdio.h>

#define vi std::vector<int>
#define MAXN 1 << 15
inline void addIfPrime(vi & primes, int n)
{
    for(vi::iterator it = primes.begin(); (*it)*(*it) <= n && it != primes.end(); it++) {
        int fract = n / (*it);
        if(fract * (*it) == n ) return;
    }
    primes.push_back(n);
}

int getPairs(vi & primes, int n)
{
    int count = 0;
    vi::iterator jt = std::upper_bound(primes.begin(), primes.end(), n);
    //printf("lower bound find %d is %d\n", n, *jt);
    for(vi::iterator it = primes.begin(); (*it) <= n && it != jt; it++)
    {
        if(std::find(it, jt, n - (*it)) != jt) {
            count++;
            //printf("%d + %d = %d\n", *it, n - (*it), n);
        }
    }
    return count;
}

int main()
{
    vi primes;
    primes.push_back(3);
    primes.push_back(5);

    //get all primes less than 2^15
    int i = 7;
    while(i <= MAXN) {
        addIfPrime(primes, i);
        i+=2;
    }
    //for(vi::iterator it = primes.begin(); it != primes.end(); it++) printf("%d ", *it); printf("\n");

    int num;
    while(scanf("%d\n", &num) != EOF && num != 0){
        int p = getPairs(primes, num);
        printf("%d\n", p);
    }
    return 0;

}
