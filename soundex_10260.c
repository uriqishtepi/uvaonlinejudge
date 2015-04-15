#include <stdio.h>

/*              ABCDEFGHIJKLMNOPQRSTUVWXYZ */
char map[27] = " 123 12  22455 12623 1 2 2";

int main ()

{

    char in[21] = {0};
    while(scanf("%s", in) != EOF) {
        char out[21] = {0};
        char *ptr = in;
        char prev = '\0';
        int optr = 0;
        while(*ptr != '\0') {
            char c = map[(*ptr - 'A')];
            if(c != prev) {
                /* printf("prev %c *ptr %c map %c \n", prev, *ptr, c); */
                if(c != ' ')
                    out[optr++] = c;
                prev = c;
            }
            ptr++;
        }
        printf("%s\n", out);

    }


    return 0;

}
