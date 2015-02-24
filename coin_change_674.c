#include<stdio.h>
#include <stdlib.h>

#define MAXI 2000
int M[] = {10, 5, 2, 1};

int find_val(int x, int A[MAXI + 1][4], int lvl) 
{
    int count = 0;
    int mul = M[lvl];
    if( mul <= x ) count += A[x-mul][lvl];

    if(lvl < 3)
        A[x][lvl] = count + find_val(x, A, lvl + 1);
    else 
        A[x][lvl] = count + 1;

    return A[x][lvl];
}

int main()
{
    int A[MAXI + 1][4] = {{0}};
    int i;
    for (i = 0; i < MAXI+1; i++) {
        find_val(i, A, 0);
        /* printf("%d-%d: %d %d %d %d\n", i*5, (i+1)*5-1, A[i][0], A[i][1],A[i][2],A[i][3]); */
    }

    int p;
    while(scanf("%d\n", &p) != EOF) {
        printf("%d\n", A[p/5][0]);
    }

    return 0;
}
