#include<stdio.h>


int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF && n >= 0) {
        long long unsigned int ln = n;
        long long unsigned int slices = (((1+ln)*ln)/2 + 1);
        printf("%llu\n", slices);            
    }

    return 0;
}   
