#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* this is a faster way to do snprintf of unsigned integers
 * verified with timing info as well as with valgrind
 *
 * timing for uint_to_ascii funC:
 * time ./uint_to_ascii 
 * dummy = 5499500
 * real    0m2.320s
 *
 * optimized is 0.7s
 *
 * timing for snprintf:
 * time ./uint_to_ascii 
 * dummy = 5500500
 * real    0m4.589s
 *
 */

int uint_to_ascii(char *str, size_t max, unsigned int num)
{
    if (max == 0) return 0;
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
    while(i >= 0 && (--max) > 0)
        *(str++) = tmp[i--];
    *str = '\0';
    return c;
}

int main()
{
    char tmp[23];
    char tmp2[23];
    int j;

    tmp[0] = 'a';
    uint_to_ascii(tmp, 0, 12345); /* cant write anything */
    assert(strcmp(tmp, "a") == 0);
    uint_to_ascii(tmp, 1, 12345); /* can only write \0 at the end */
    assert(strcmp(tmp, "") == 0);
    uint_to_ascii(tmp, 2, 12345); /* dont forget the \0 at the end */
    assert(strcmp(tmp, "1") == 0);
    uint_to_ascii(tmp, 3, 12345); /* dont forget the \0 at the end */
    assert(strcmp(tmp, "12") == 0);

   
    int dummy = 0; /* added to avoid optimization of the for loop */
    for(j = 0; j < 1000000; j++) {
        int len = 0;
        len += uint_to_ascii(tmp, sizeof(tmp), j);
        tmp[len] = '-';
        uint_to_ascii(tmp + len + 1, sizeof(tmp) - len, j);

        snprintf(tmp2, sizeof(tmp2), "%u-%u", j,j);
        if(strcmp(tmp, tmp2) != 0) abort();
        /*
        if (tmp[8] >= '5')
            dummy++;
            */
    }
    printf("dummy = %d\n", dummy);
    return 0;
}
