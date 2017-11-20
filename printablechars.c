#include<stdio.h>

int main()
{
    char c;
    while(scanf("%c", &c) != EOF) {
        if(32 < c && c < 128) putchar(c);
    }

    return 0;
}
