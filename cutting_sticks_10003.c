/*
 * dynamyc programming approach, 
 * C(0,N) = L (0,N) + min k=0,N-1 { C(0,k) + C(k+1, N) }
 *
 * 4 6 8 are the cuts, soo 4 2 2 2 are the lengths in that order, so
 * every consecutive sum
 *
 * L: 
 *
 * 4 6 8 10
 *   2 4  6
 *     2  4
 *        2
 *
 * C:
 * 0 6 12 20
 *   0  4 10 
 *      0  4
 *         0
 *
 * for(d = 3; d < N; d++)
 *   //find min for this level
 *   for(i=1;i<d;i++)
 *     min = MIN(min, C[d-1][i] + ?)
 *   C[d][i] = D[d][i] + min;
 *
 * 
 */


#include<stdio.h>
#include<assert.h>
#define out 
#define MAXSZ 50

int main()
{
    int l;
    while(scanf("%d\n", &l) != EOF && l != 0) {
        assert(l > 0 && l < 1000);

        int n;
        int arr[MAXSZ+3] = {0};  /* array with cuts */
        scanf("%d\n", &n);
        assert(n < MAXSZ);

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

        printf("The minimum cutting is %d.\n", C[0][n]); 
    }


    return 0;

}
