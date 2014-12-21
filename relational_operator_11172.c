#include <stdio.h>
int main ()
{
    int t;
    scanf("%d", &t);

    int count = 0;
    while(count++ < t) {
        int a, b;
        scanf("%d %d\n", &a, &b);
        if(a > b) printf(">");
        else if(a < b) printf("<");
        else printf("=");
        printf("\n");
    }
    return 0;
}
