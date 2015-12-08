#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXL 10
enum ty {none, vowel, consonant};


void print_end_of_word(int * type, char start_char) 
{
    if(*type == consonant)
        printf("%c", start_char);
    printf("a");
    printf("y");
    *type = none;
}

int get_type(char start_char) 
{
    switch(start_char) {
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
            return vowel;
            break;
        default:
            return consonant;
            break;
    };
}

int main()
{
    char str[MAXL+1];
    int type = none;
    char start_char = 0;

    while(fgets(str, MAXL, stdin) != NULL) 
    {
        char * sptr = str;
        while(sptr !=NULL && *sptr != '\0') 
        {
            if( !((*sptr >= 'a' && *sptr <= 'z' ) || 
                        (*sptr >= 'A' && *sptr <= 'Z' )  )) 
            {
                if(type != none) print_end_of_word(&type, start_char);
                printf("%c", *sptr);
                sptr++;
                continue;
            }

            /* else this char is the beginning of a word */

            if(type == none) {
                start_char = *sptr;
                type = get_type(start_char);
                if(type == vowel)
                    printf("%c", start_char);

                sptr++;
            }

            while(sptr != NULL && *sptr != '\0' && 
                    ((*sptr >= 'a' && *sptr <= 'z' ) || 
                    (*sptr >= 'A' && *sptr <= 'Z' ) ) ) 
            {
                printf("%c", *sptr);
                sptr++;
            }
        }
    }
    if(type != none) print_end_of_word(&type, start_char);

    return 0;
}
