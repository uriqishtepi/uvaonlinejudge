#include<stdio.h>
#include <string.h>

int foo(int *a)
{
    printf("%d\n", *a);
    return 0;
}


int main()
{
    char *str = NULL;
    if (str != NULL)
        printf("len(null) = %d\n", strlen(str));

    int i;
    int b;
    for(i = 0; i <=256; i++) {
        memcpy(&b, &i, sizeof(int));
        foo(&b);
    }

    return 0;
}
