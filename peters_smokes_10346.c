#include<stdio.h>

int getNumCig(int n, int k) 
{
    /* printf("getNumCig %d %d\n", n, k); */
    int num = n / k;
    int rem = n % k;

    if(num + rem >= k) 
        num += getNumCig(num + rem, k);
    return num;
}

int main() 
{
    int n, k;
    while(scanf("%d %d", &n, &k) != EOF) {
        int num = n + getNumCig(n,k);
        printf("%d\n",num);
    }

    return 0;
}
