#include <stdio.h>
int main ()
{
    int v, t;
    while(scanf("%d %d\n", &v, &t) != EOF) {
        int d = 2 * v * t;
        printf("%d\n", d);
    }
    return 0;
}
