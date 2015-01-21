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
        printf("n %d str %s ", n, str);
        if(strcmp(copy, str) == 0) {
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
        int j;
        int found = 0;
        for(i = n - 2; i >= 0 && found == 0; i--) {
            for(j = i + 1; j < n && found == 0; j++) {
                if(str[i] < str[j]) 
                    found = 1;
            }
        }
        if(found) {
            /* find actual min 
            int j;
            for(j = i+1; j < n; j++) if(str[min] > str[j]) min = j;*/
            swap(str, i, j);
            if(n - i > 1)
                qsort(str + i, n - i, sizeof(char), cmpchars);
            printf("--> n %d str %s\n", n, str);
        }
        else
            printf("last in sequence.\n");
    }

    return 0;
}
