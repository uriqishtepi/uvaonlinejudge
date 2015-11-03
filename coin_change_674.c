/* find combinations of coin representation in multples of
 * 50, 25, 10, 5, 1
 *
 * the trick is to realize that once you extract largest
 * value, say 50 from you number, you now have to represent
 * the remaining sum with any combination of 50 or below.
 * Then if you were to remove next value, 25, you would need
 * to represent te combinations of your sum - 25 with 
 * combinations of coins 25 or below -- ie you can not use 50:
 * so if we have levels of what is allowed 5,4,3,2,1 for 50,25,10,5,1:
 * M(5, 5) = M(5,4) = M(5,3) = M(5,2) = M(0,2) + M(0,1) = 1+1 = 2
 * M(10,5) = M(10,4) = M(10,3) = M(0,3) + M(5,2) + M(9,1) = 1 + 2 + 1 = 4
 *                               ..-10 ...  -5 ..... -1
 *
 * M(10,2) = M(5,2) + M(9,1) = 2 + 1 = 3
 *            -5       -1
 * M(15,5-3) = M(5,3) + M(10,2) + M(14,1) = 2 + 3 + 1 = 6
 *              -10    ... -5       -1
 *
 * M(15, 2) = M(10,2) + M(14,1) = 3 + 1 = 4
 * M(20, 2) = M(15,2) + M(19,1) = 4 + 1 = 5
 * M(20, 3) = M(10,3) + M(15,2) + M(19,1) = 4 + 4 + 1 = 9
 *
 * M(25,3) = M(15,3) + M(20,2) + M(19,1) = 6 + 5 + 1 = 12
 *
 * M(25,5) = M(25,4) = M(0,4) + M(15,3) + M(20,2) + M(24,1) = 1 + 6 + 5 + 1 = 13
 *                  ... -25 .... -10  ...  -5   .... -1 
 *
 * to form a table:
 *
 *   M     50   25   10    5    1
 *
 *   lvl    5    4    3    2    1
 *   -----------------------------
 *  0- 4    1    1    1    1    1
 *  4- 9    2    2    2    2    1
 * 10-14    4    4    4    3    1
 * 15-19    6    6    6    4    1
 * 20-24    9    9    9    5    1
 * 25-29   13   13   12    6    1
 * 
 * The below compresses this table further to look like this:
 *
 * 0-4: 1 1 1 1
 * 5-9: 2 2 2 2
 * 10-14: 4 4 4 3
 * 15-19: 6 6 6 4
 * 20-24: 9 9 9 5
 * 25-29: 13 13 12 6
 * 30-34: 18 18 16 7
 * 35-39: 24 24 20 8
 * 40-44: 31 31 25 9
 * 45-49: 39 39 30 10
 * 50-54: 50 49 36 11
 *
 *
 */
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
