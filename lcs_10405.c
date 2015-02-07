#include<stdio.h>
#include<string.h>
#include<sys/param.h>
#include<assert.h>

#define out printf
#define MAXS 2001

/* longest common substring */

int main()
{
    char stra[MAXS+10] = {0};
    char strb[MAXS+10] = {0};
    while( fgets(stra, MAXS, stdin) != NULL)
    {
        char* rc = fgets(strb, MAXS, stdin);
        assert(rc != NULL);
        out("'%s'\n'%s'\n", stra,strb);
        int m = strnlen(stra, MAXS);
        int n = strnlen(strb, MAXS);
        if(m == 0 || n == 0) {
            printf("0\n");
            continue;
        }

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
    }

    return 0;
}
