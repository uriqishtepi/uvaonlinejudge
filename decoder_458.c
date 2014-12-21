#include <stdio.h>
int main ()
{
    int v, t;
    char d =  '*'-'1';
    char * buff = NULL;
    size_t n;
    int count;
    while((count = getline(&buff, &n, stdin)) > 0) {
        size_t i;
        for(i = 0; i < count && buff[i] != '\n'; i++) {
            printf("%c", buff[i]+d);
        }
        printf("\n");
    }
    return 0;
}
