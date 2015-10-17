/*
change ordering of letters a b c d:

 3 1 4 2 

 does NOT mean:
 c a d b

 but it means:
 b d a c

 that means that a goes to 3rd position, etc

*/

#include<stdio.h>
#include<string.h>
#include<sys/param.h>
#include<assert.h>

#define MAXS 1000

/* longest common substring */
void readLine(char *v, int n)
{
    int i = 0;
    while(i < n) {
        int num;
        if(scanf("%d", &num) == EOF) {
            if(i != 0 ) printf("Too few numbers for this entr\n");
            exit(0);
        }
        assert(num >= 1 && num <= n);
        /* Not this way: v[i] = num + 'a'; */
        v[num-1] = i + 'a';
        i++;
    }
}


int main()
{
    char v1[21] = {0};
    char v2[21] = {0};
    int m;
    scanf("%d\n", &m);
    int n = m;
    readLine(v1, n);
    while(--m > 0) {
        readLine(v2, n);

        int C[MAXS+300][MAXS+300] = {{0}};

        int i;
        int j;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= n; j++) {
                if (v1[i-1] == v2[j-1]) 
                    C[i][j] = C[i-1][j-1] + 1;
                else
                    C[i][j] = MAX(C[i-1][j], C[i][j-1]);
            }
        }
        printf("%d\n", C[n][n]);
    }

    return 0;
}
