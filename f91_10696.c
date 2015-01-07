#include<stdio.h>

int f91(int N)
{
    if(N <= 100) return f91(f91(N+11));
    else return N - 10;
}

int main()
{
    int i;
    while(scanf("%d\n", &i) != EOF && i != 0) {
        printf( "f91(%d) = %d\n", i, f91(i));
    }
    return 0;
}

