/*
 * dynamyc programming approach, 
 * 4 6 8 are the cuts, soo 4 2 2 2 are the lengths in that order, so
 * every consecutive sum
 * 4 2 2 2
 * 6 4 4
 * 8 6
 * 10
 *
 *
 * 4  2  2  2
 * 6  4  4
 * @ = 8 + min(6, 4) = 8 + 4
 *    @ = 6 + min(4,4)   
 *12  10 
 * @ = 10 + min(12,10) = 20
 * 20
 *
 *
 * next example, cuts 2 4 7, lengths 2 2 3 3
 * 0    2  2  3  3
 * 1    4  5  6
 * 2    7  8 
 * 3   10
 *
 * 0   0  0  0  0
 * 1   4  5  6  
 *     @ = 7 + min(4,5) = 7 + 4
 *        @ = 8 + min(5,6) = 8 + 5
 * 2  11 13
 *     @ = 10 + min(11,13,4+6)  = 10 + 10
 * 3  20
 * (NOT 10 + min(11,13) => 21)
 *
 * C[1,0] = 4 + min(C[0,0],C[0,1])
 * C[2,0] = 7 + min(C[1,0],C[1,1]
 * C[3,0] = 10 + min(C[2,0],C[2,1],C[1,0]+C[1,2])
 *
 * 
 * C[4,0] = D[4,0] + min(C[3,0],C[3,1],C[3,2],C[
 *
 * for(d = 3; d < N; d++)
 *   //find min for this level
 *   for(i=1;i<d;i++)
 *     min = MIN(min, C[d-1][i] + ?)
 *   C[d][i] = D[d][i] + min;
 *
 *
 *
 *  3  7  2  8  4 1 
 * 10  9 10 12  5 
 * 12 17 14 13 
 * 20 21 15 
 * 24 22 
 * 25 
 * 
 *
 * previous:
 *
greedy:
pick the one that breaks the range closer to half, if you have an ambiguous 
choice, choose side that has more cuts and items in it (is this correct?).

0......10
  4 6 8 
cutting at 4 leaves size 6 cut at 6 or 8, so 10 + 6 + 4
cutting at 6 however leaves sizes 6 and 4 with, 10 + 6 + 4
hmm, this looks like dynamic programming, where you join together 
pieces two at a time:

0....4..6..8...10

*/



#include<stdio.h>
#include<assert.h>
#define out 
#define MAXSZ 50

int main()
{
    int l;
    while(scanf("%d\n", &l) != EOF && l != 0) {
        assert(l > 0 && l <= 1000);

        int n;
        int arr[MAXSZ+3] = {0};  /* array with cuts */
        scanf("%d\n", &n);
        assert(n > 0 && n <= MAXSZ);

        int i = 0;
        int last = 0;
        while(i < n) {
            int curr;
            scanf("%d", &curr);
            assert(curr > last && curr <= l);
            arr[i] = curr - last;
            last = curr;
            i++;
        }
        arr[i] = l - last;

        /*
        for(i=0;i<=n;i++) printf("%d ", arr[i]);
        printf("\n\n"); 
        */

        int j;
        int L[MAXSZ+3][MAXSZ+3] = {{0}};
        for(i=0;i<=n;i++) {
            L[i][i] = arr[i];
        }
        int d;
        /*
        L 0,1 
        L 1,2
        L 2,3...
        L 0,2
        L 1,3...
        */
        for(d=1;d<=n;d++) {
            for(i=0;i<=(n-d);i++) {
                j = i+d;
                L[i][j] = L[i][j-1] + L[j][j];
            }
        }

        /*
        for(i=0;i<=n+2;i++) {
            for(j=0;j<=n+2;j++) {
                printf("%3d ", L[i][j]);
            }
            printf("\n");
        }
        printf("\n"); 
        */

        int C[MAXSZ+3][MAXSZ+3] = {{0}};
        /*
        for(i=0;i<=n;i++) {
            C[i][i] = arr[i];
        }*/

        for(d=1;d<=n;d++) {
            for(i=0;i<=(n-d);i++) {
                j = i+d;
                int k;
                int min = 100000000;
                for(k=i;k<j;k++) {
                    int curr = C[i][k] + C[k+1][j];
                    out("C(%d,%d)+C(%d,%d): %d+%d = %d\n", i, k, k+1, j, C[i][k], C[k+1][j], curr);
                    if(min > curr)
                        min = curr;
                }
                if(min == 100000000) min = 0;
                C[i][j] = L[i][j] + min;
                out("C(%d,%d)=%d + %d\n", i, j, L[i][j], min);
            }
        }

        /*
        for(i=0;i<=n+2;i++) {
            for(j=0;j<=n+2;j++) {
                printf("%3d ", C[i][j]);
            }
            printf("\n");
        }
        printf("\n"); 
        */

        printf("%d\n", C[0][n]); 
    }


    return 0;

}
