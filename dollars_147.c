/* similar to coin change
 */

#include <stdio.h>
#define     ITEMS 1 + (30000/5)
int Y[] = {1,2,4,10,20,40,100,200,400,1000,2000};
#define  LVLS sizeof(Y)/sizeof(int)


void findM(long long int M[][LVLS], int curr, int lvl)
{
    int t = lvl;
    while(t >= 0) {
        int next = curr - Y[t];
        if(next >= 0)
            M[curr][lvl] += M[next][t];
        t--;
    }
    /* printf("%lld ", M[curr][lvl]); */
}

int main()
{
    float fval;
    int ival;
    long long int M[ITEMS][LVLS] = {{0LL}};
    int i;
    int lvl;
    for(lvl = 0; lvl < LVLS; lvl++)
        M[0][lvl] = M[1][lvl] = 1;
    for(i = 2; i <= ITEMS; i++) {
        /* printf("%d: ", i); */
        for(lvl = 0; lvl < LVLS; lvl++)
            findM(M, i, lvl);
        /* printf("\n"); */
    }
    while(scanf("%f", &fval) != EOF && (ival = fval * 100) != 0) {
        printf("%6.2f%17lld\n", fval, M[ival/5][LVLS-1]);
    }
    return 0;
}
