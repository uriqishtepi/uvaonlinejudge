#include<stdio.h>
#include<string.h>
#include<sys/param.h>
#include<assert.h>

#define out 
#define MAXS 1000

/* longest common substring */
int main()
{
    char * buff1 = NULL;
    char * buff2 = NULL;
    int n1, n2, i, j;
    while( getline(&buff1, &n1, stdin) >= 0 && 
           getline(&buff2, &n2, stdin) >= 0 )
    {
        int C[MAXS+2][MAXS+2] = {{0}};
        char stra[MAXS+1] = {0};
        int m = 0;
        sscanf(buff1, "%s%n", stra, &m);
        char strb[MAXS+1] = {0};
        int n = 0;
        sscanf(buff2, "%s%n", strb, &n);
        out("'%s'\n'%s'\n", stra,strb);

        assert( m == strnlen(stra, MAXS+1));
        assert(m >= 0 && m <= MAXS);

        assert( n == strnlen(strb, MAXS));
        assert(n >= 0 && n <= MAXS);


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
