#include<stdio.h>

int sum_digits(int n)
{
    if(n < 10) return n;
    int res = 0;
    while(n > 0) {
        res += n % 10;
        n /= 10;
    }
    return sum_digits(res);
}

int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF && n != 0) {
        printf("%d\n", sum_digits(n));
    }

    return 0;
}
