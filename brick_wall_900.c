#include <stdio.h>


int main () 
{
    int n;
    int i;
    int C[51] = {0};
    C[0] = 1;
    C[1] = 1;
    for(i=2;i <= 51;i++) {
        C[i] = C[i-1] + C[i-2];
    }

    while( scanf("%d", &n) != EOF && n > 0) {
        printf("%d\n", C[n]);
    }

    return 0;
}
