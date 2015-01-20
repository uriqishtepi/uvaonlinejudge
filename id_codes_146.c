#include<stdio.h>
#include <stdlib.h>
#include <string.h>

static int
cmpchars(const void *p1, const void *p2)
{
    char c1 = *(const char*) p1;
    char c2 = *(const char*) p2;
    /* printf("comparing %c %c\n", c1, c2); */
    return c1 < c2;
}

int main()
{
    int n;
    char str[256];
    char copy[256];
    while(scanf("%s%n", str, &n) != EOF && str[0] != '#') {
        strcpy(copy, str);
        printf("n %d str %s\n", n, str);
        qsort(str, n, sizeof(char), cmpchars);
        printf("n %d str %s\n", n, str);
        if(strcmp(copy, str) == 0) {
            printf("last in sequence.\n");
            continue;
        }
    }

    return 0;
}
