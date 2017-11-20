#include<stdio.h>
#include <string.h>

int uint_to_ascii(char *str, unsigned int num)
{
    int tmp[11];
    int c = 0;
    if (num == 0) {
        tmp[0] = '0';
        c = 1;
    }

    while(num > 0) {
        int f = num/10;
        tmp[c++] = '0' + (num - f * 10);
        num = f;
        /* printf("f = %d tmp[c] %c\n", f, tmp[c]); */
    }
    int i = c - 1;
    while(i >= 0)
        *(str++) = tmp[i--];
    *str = '\0';
    return c;
}

int main()
{
    char tmp[23];
    char tmp2[23];
    int j;
    for(j = 0; j < 100000; j++) {
        int len = 0;
        len += uint_to_ascii(tmp, j);
        tmp[len] = '-';
        uint_to_ascii(tmp + len + 1, j);
        sprintf(tmp2, "%u-%u", j,j);
        if(strcmp(tmp, tmp2) != 0) abort();
    }

    return 0;
}
