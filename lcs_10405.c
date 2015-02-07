#include<stdio.h>
#include<string.h>
#include<sys/param.h>
#include<assert.h>

#define out 
#define MAXS 1000

/* longest common substring */

int main()
{
    char * stra = NULL;
    char * strb = NULL;
    int n1, n2;
    int m, n;
    while( (m = getline(&stra, &n1, stdin) ) >= 0 && 
           (n = getline(&strb, &n2, stdin) ) >= 0 ) 
    {
        out("'%s'\n'%s'\n", stra,strb);
        int C[MAXS+200][MAXS+200] = {{0}};

        if(m > 0 && stra[m-1] == '\n') m--;

        if(n > 0 && strb[n-1] == '\n') n--;

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
        free(stra);
        free(strb);
        stra = NULL;
        strb = NULL;
    }

    return 0;
}
