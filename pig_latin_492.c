#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char str[2048];
    int len;

    while(scanf("%s", str) != EOF) {
        len = strlen(str);
        if(len > sizeof(str)-3) exit(1);

        switch(str[0]) {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
                str[len] = 'a';
                str[len+1] = 'y';
                str[len+2] = '\0';
                printf("%s\n", str);
                break;
            default:
                str[len] = str[0];
                str[len+1] = 'a';
                str[len+2] = 'y';
                str[len+3] = '\0';
                printf("%s\n", str+1);
                break;
        };
    }

    return 0;
}
