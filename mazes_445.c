#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int multdigits(int num)
{
    int ret = 0;
    while(num > 0) {
        ret += num % 10;
        num = num /10;
    }
    return ret;
}


int main()
{
    char * buff = NULL;
    size_t n;
    int len;
    while((len=getline(&buff, &n, stdin)) >= 0) {
        /* printf("got line '%s' len %d\n", buff, len); */
        if(len <= 2) { /* new maze */
            printf("\n");
            continue;
        }
        char * tok = strtok(buff, "\n!");
        while(tok != NULL && strlen(tok) > 0) {
            /* printf("tok '%s'\n", tok); */
            int read = 0;
            int num;
            char letter;
            while(sscanf((tok+=read),"%d%c%n", &num, &letter, &read) != EOF)
            {
                int i;
                num = multdigits(num);
                if(letter == 'b') letter = ' ';
                /* something about asterisc */
                for(i=0;i<num;i++) printf("%c", letter);
            }
            printf("\n");
            tok = strtok(NULL, "\n!");   
        }
    }


    return 0;
}
