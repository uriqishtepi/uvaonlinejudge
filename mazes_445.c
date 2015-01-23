#include<stdio.h>
#include<stdlib.h>
#include <string.h>

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
            int num = 0;
            char letter;
            while(sscanf((tok+=read),"%c%n", &letter, &read) != EOF)
            {
                int i;
                if(letter >= '0' && letter <= '9') {
                    num += letter - '0';
                    continue;
                }
                if(letter == 'b') letter = ' ';
                /* something about asterisc */
                for(i=0;i<num;i++) printf("%c", letter);
                num = 0;
            }
            printf("\n");
            tok = strtok(NULL, "\n!");   
        }
    }


    return 0;
}
