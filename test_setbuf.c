#include <stdio.h>

int main(void)
{
    setvbuf(stdin, 0, _IOFBF, 0);
    int i = 0;
    char line[1024];

    for (i = 0; i < 1023; i++)
        line[i] = 't';
    line[1023] = '\0';

    for (i = 0; i < 100000; i++)
       printf("%d - %s\n", i, line);
   return 0;
}
