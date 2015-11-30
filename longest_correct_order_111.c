/*
 longest common substring 
change ordering of letters a b c d:

 3 1 4 2 

 does NOT mean:
 c a d b

 but it means:
 b d a c

 that means that a goes to 3rd position, etc

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/param.h>
#include<assert.h>

#define MAXS 20

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
    assert(m >= 1 && m <= 21);

    int n = m;
    readLine(v1, n);
    while(--m > 0) {
        readLine(v2, n);

        int C[MAXS+2][MAXS+2] = {{0}};

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
