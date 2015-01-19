#include<vector>
#include<stdio.h>
#define vi std::vector<int>

unsigned char arr[1000001] = {0, 0, 1, 1, 0, 1, 0};
vi primes;
int lastint = 5;

void find_primes_upto( int n)
{
    //printf("find_primes_upto %d\n", n);
    int i;
    for(i = lastint+2; i <= n; i+= 2) { 
        //printf("find_primes_upto ...%d\n", i);
        int prime = 1;
        for(vi::iterator it = primes.begin(); it != primes.end(); ++it) {
            if((i % *it) == 0) {
                prime = 0;
                //printf("find_primes_upto ...%d is NOT prime, div by %d\n", i, *it);
                break;
            }
        }
        if(prime) { 
            arr[i] = 1; 
            primes.push_back(i); 
            //printf("find_primes_upto ...%d is prime\n", i);
        }
    }
    lastint = i - 2;
}

int main()
{
    int n;
    primes.push_back(3);
    primes.push_back(5);
    while(scanf("%d\n", &n) != EOF && n != 0) {
        if(lastint < n) {
            find_primes_upto(n);
        }

        int found = 0;

        for(vi::iterator it = primes.begin(); it != primes.end(); ++it) {
            if(arr[n - *it]) {
                found = 1;
                printf("%d = %d + %d\n", n, *it, n - *it);
                break;
            }
        }
        if(!found) 
            printf("Goldbach's conjecture is wrong.\n");
    }

    return 0;
}
