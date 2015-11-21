/* similar to coin change
 * find the number of combinations to change up to $300.00 in
 * 5c,10c,...,100$
 */

#include <stdio.h>
#include <assert.h>

int Y[] = {1,2,4,10,20,40,100,200,400,1000,2000};
#define LVLS      (sizeof(Y)/sizeof(int))
#define MAXIT     30000
#define ITEMS     (1 + (MAXIT/5))
#define debug 0


void findM(unsigned long long int M[][LVLS], int curr, int lvl)
{
    assert(lvl < LVLS);
    int t = lvl;
    while(t >= 0) {
        int next = curr - Y[t];
        if(next >= 0)
            M[curr][lvl] += M[next][t];
        t--;
    }
    if(debug) printf("%llu ", M[curr][lvl]);
}


int main()
{
    float fval;
    unsigned long long int M[ITEMS][LVLS] = {{0}};
    int i;
    int lvl;

    for(lvl = 0; lvl < LVLS; lvl++)
        M[0][lvl] = M[1][lvl] = 1;
    for(i = 2; i <= ITEMS; i++) {
        if(debug) printf("%d: ", i);
        for(lvl = 0; lvl < LVLS; lvl++)
            findM(M, i, lvl);
        if(debug) printf("\n");
    }

    /* printf("300.00%17llu\n", M[30000/5][LVLS-1]); */
    while(scanf("%f", &fval) != EOF)
    {
        int ival = (int) (fval * 10000) / 100;
        if(ival < 1) break;

        int md10 = (ival % 10);
        /* printf("md10 %d ival %d ", md10, ival); */
        assert(md10 == 0 || md10 == 5);
        int offset = ival/5;
        assert(offset >= 0 && offset <= MAXIT);

        printf("%6.2f%17llu\n", fval, M[offset][LVLS-1]);
    }
    return 0;
}
