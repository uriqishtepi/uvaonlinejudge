/*
 * 3025 -> (30+25)^2 -> 3025
 *
 * for two digits need to search:
 * 00
 * 01
 * 02
 * 03
 * ...
 * 99
 * for 8 need to search;
 * 00000000
 * 00000001
 * ...
 * 99999999
 *
 * to speedup can do binary srch for the second loop
 * also should be caching the results 
 */

#include<stdio.h>
int mypow(int a, int b)
{
    int res = 1;
    while(b-- > 0) {
        res *= a;
    }
    return res;
}

void find_vals(int n)
{
    int i; 
    int j;
    int h = n / 2;
    int max = mypow(10, h);

    for(i=0; i<max; i++) {
        for(j=0;j<max;j++){
            int sum = i + j;

            int prod = sum * sum;
            int val = max * i + j;
            if(prod > val) break;

            if(prod == val) {
                printf("%.*d%.*d\n", h, i, h, j);
                /*equivalent printf("%2$.*1$d%3$.*1$d\n", h, i, j); */
            }
        }
    }
}

int main()
{
    int n = 8;
    while(scanf("%d\n", &n) != EOF) {
        find_vals(n);
    }
    return 0;
}
