#include<vector>
#include<algorithm>
#include<stdio.h>
#include<assert.h>
#include <string.h>

#define vi std::vector<int> 

void addIfPrime(vi & primes, int n)
{
    for(vi::iterator it = primes.begin(); it!=primes.end();it++) {
        int fraction = n / (*it);
        if(fraction * (*it) == n) 
            return;
    }
    primes.push_back(n);
}

int main()
{
    vi primes;
    int i;
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    for(i = 7; i < 2000; i+=2) {
        addIfPrime(primes, i);
    }
    primes.insert(primes.begin(), 1);

    char c;
    int sum = 0;
    char arr[21] = {0};
    int count = 0;
    while(1) {
        int rc = scanf("%c", &c);
        if(c == '\n' || rc == EOF) {
            if(sum == 0) break;
            //printf("arr %s sum %d\n", arr, sum);
            if(std::binary_search(primes.begin(), primes.end(), sum))
                printf("It is a prime word.\n");
            else
                printf("It is not a prime word.\n");
            if(rc == EOF) break;
            sum = 0;
            count = 0;
            memset(arr, 0, 20);
            continue;
        }

        assert(('a' <= c && c <= 'z' ) || ('A' <= c && c <= 'Z' ));
        sum += c >= 'a' ? c - 'a' + 1 : c - 'A' + 27;
        arr[count++] = c;
    }
    return 0;
}
