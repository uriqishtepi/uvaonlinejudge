#include<stdio.h>
#include<string.h>
#include<sys/param.h>

#define out 

/* longest common substring */

int main()
{
    char stra[1001];
    char strb[1001];
    while(scanf("%s\n%s\n", stra, strb) != EOF) {
        out("%s\n%s\n", stra,strb);
        int C[1002][1002] = {{0}};
        int m = strlen(stra);
        int n = strlen(strb);
        int i;
        int j;
        for(i = 1; i <= m; i++) {
            for(j = 1; j <= n; j++) {
                if (stra[i-1] == strb[j-1]) 
                    C[i][j] = C[i-1][j-1] + 1;
                else
                    C[i][j] = MAX(C[i-1][j], C[i][j-1]);
out("%d ", C[i][j]);
            }
out("\n");
        }
        printf("%d\n", C[m][n]);
    }

    return 0;
}
