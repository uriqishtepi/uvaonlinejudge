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
        /* printf("n %d str %s ", n, str); */
        if(strcmp(copy, str) == 0) {
            continue;
        }
                int i;
        for(i = n -1; i > 0; i--) {
            if(str[i - 1] < str[i])
                break;
        }
        if(i > 0) {
            /* find actual min greater than str[i-1] */
            int j;
            int min = i;
            for(j = min+1; j < n; j++) 
                if(str[i] > str[j] && str[i - 1] < str[j]) 
                    min = j;
            swap(str, i-1, min);
            if(n - i > 1)
                qsort(str + i, n - i, sizeof(char), cmpchars);
            printf("%s\n", str);
        }
        else
            printf("No Successor\n");
    }

    return 0;
}
