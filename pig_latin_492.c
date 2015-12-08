#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXL 1024

int main()
{
    char str[MAXL+1];
    int type;
    enum ty {vowel, consonant};

    while(fgets(str, MAXL, stdin) != NULL) {
        char * start = str;
        char * end;
        while(start !=NULL && *start != '\0') {
            if( !((*start >= 'a' && *start <= 'z' ) || 
                        (*start >= 'A' && *start <= 'Z' )  )) 
            {
                printf("%c", *start);
                start++;
                continue;
            }

            switch(*start) {
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
                    type = vowel;
                    printf("%c", *start);
                    break;
                default:
                    type = consonant;
                    break;
            };

            end = start+1;
            while(end != NULL && *end != '\0' && 
                    ((*end >= 'a' && *end <= 'z' ) || 
                    (*end >= 'A' && *end <= 'Z' ) ) ) 
            {
                printf("%c", *end);
                end++;
            }

            if(type == consonant)
                printf("%c", *start);
            printf("a");
            printf("y");
            start = end;
        }
    }

    return 0;
}
