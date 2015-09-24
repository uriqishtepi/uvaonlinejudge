/* lcs type problem
*/

#include <stdio.h>
#include<sys/param.h>
#define MAXSZ 100

/* longest common substring */
int lcs( int * arr1, int m1, int * arr2 , int m2)
{
    int M[MAXSZ+1][MAXSZ+1]={{0}};
    int L[MAXSZ+1][MAXSZ+1]={{0}};
    int i;
    int j;

    for(i = 0; i < m1; i++)
        L[i][0] = i;

    for(i = 1; i <= m1; i++)
    {
        for(j = 1; j <= m2; j++)
        {
            if(arr1[i] == arr2[j]) 
                M[i][j] = M[i-1][j-1] +1;
            else
                M[i][j] = MAX(M[i-1][j], M[i][j-1]);
        }
    }
    return M[m1][m2];
}

int main()
{
    int m1, m2;
    int cnt = 0;
    while(scanf("%d %d", &m1, &m2) != EOF && m1 !=0 && m2 != 0) {
        int i;
        int arr1[MAXSZ] = {0};
        int arr2[MAXSZ] = {0};

        for(i=0; i<m1; i++) {
            scanf("%d", &arr1[i]);
        }
        for(i=0; i<m2; i++) {
            scanf("%d", &arr2[i]);
        }
        int l = lcs(arr1, m1, arr2, m2);
        if(cnt > 0) printf("\n");
        printf("Twin Towers #%d\n", cnt+1);
        printf("Number of Tiles : %d\n", l);
        cnt++;
    }
    return 0;
}

