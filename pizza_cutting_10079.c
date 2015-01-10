#include<stdio.h>


int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF && n >= 0) {
        int i;
        int slices = 1;
        for(i = 1; i <= n; i++) {
            slices += i;
/* printf("%d %d\n", i, slices);             */
        }
        printf("%d\n", slices);            
    }

    return 0;
}   
