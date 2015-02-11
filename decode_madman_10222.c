#include<stdio.h>
#include <ctype.h>

int main ()
{
    char * low = "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
    char * up =  "~!@#4%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?";
    char map[256] = {0};
    int i; 
    char c;

    for(i = 0; i < strlen(low); i++) {
        map[low[i]] = tolower(low[i - 2]);
        map[up[i]] = tolower(up[i - 2]);
    }
    map['\n'] = '\n';
    map[' '] = ' ';

    /*
    for(i = 2; i < strlen(low); i++) {
        //printf("%c\n", map[low[i]]);
        printf("%c\n", map[up[i]]);
    }
    */

    while(scanf("%c", &c) != EOF) { printf("%c", map[c]); }

    return 0;
}
