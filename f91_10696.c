#include<stdio.h>

int f91(int N)
{
    if(N <= 100) return f91(f91(N+11));
    else return N - 10;
}

int main()
{
    for(i = 0; i < 2000000; i++)
        printf( "%d %d\n", i, f91(i));
    return 0;
}

