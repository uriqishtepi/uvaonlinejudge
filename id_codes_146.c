#include<stdio.h>
#include <stdlib.h>
#include <string.h>

static int
cmpchars(const void *p1, const void *p2)
{
    char c1 = *(const char*) p1;
    char c2 = *(const char*) p2;
    /* printf("comparing %c %c\n", c1, c2); */
    return c1 > c2;
}

void swap (char * str, int i, int j)
{
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
}

int main()
{
    int n;
    char str[256];
    char copy[256];
    while(scanf("%s%n\n", str, &n) != EOF && str[0] != '#') {
        printf("n %d str %s\n", n, str);
        if(strcmp(copy, str) == 0) {
            printf("last in sequence.\n");
            continue;
        }
        /* needd to produce combinations, sort them and find the next 
        is there a better way? all i need is the next one.
        so if we have ab, we need ba. so we do one flip...

        if we have abc we need acb:
            abc acb bac bca cab cba

        abcd abdc bacd cabd cbad dabc dbac dbca dcab dcba
        if we have ababb -> abbab -> abbba
        start from the end, find the first letter pair that needs flipping
        then sort from that point to the end
        */
        int i;
        for(i = n-1; i >0; i--) {
            if(str[i-1] < str[i])
                break;
                /* sort from i+i to n */
        }
        if(i > 0) {
            /*find actual min */
            swap(str,i-1,i);
            if(n - i > 1)
                qsort(str+i, n-i, sizeof(char), cmpchars);
        }
        printf("n %d str %s\n", n, str);
    }

    return 0;
}
