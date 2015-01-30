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
    while( getline(&stra, &n1, stdin) >= 0 && getline(&strb, &n2, stdin) >= 0) 
    {
        out("%s\n%s\n", stra,strb);
        int C[MAXS+2][MAXS+2] = {{0}};

        int m = strnlen(stra, MAXS+1);
        if(stra[m-1] == '\n') m--;
        if(m > MAXS) m = MAXS;
        assert(m >= 0 && m <= MAXS);

        int n = strnlen(strb, MAXS);
        if(strb[n-1] == '\n') n--;
        if(n > MAXS) n = MAXS;
        assert(n >= 0 && n <= MAXS);

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
