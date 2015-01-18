#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char num[1024];
    char sum[1024] = {0};
    while(scanf("%s\n", num) != EOF) {
        int nlen = strnlen(num, sizeof(num));
        int pos = 0;
        while (nlen-- > 0) {
            /* add num[nlen] to sum[pos] */
            if(sum[pos] > 0) {
                int digit = num[nlen] - '0';
                sum[pos] += digit;
                /* propagate carry */
                int i = pos;
                while(sum[i] > '9') {
                    sum[i] -= 10;
                    sum[i+1] = sum[i+1] > 0 ? sum[i+1] + 1 : '1';
                    i++;
                }
            }
            else sum[pos] = num[nlen];
            /* printf("a %d %d %d %d\n", nlen, num[nlen], pos, sum[pos]); */
            pos++;
        }
    }
        int pos = 0;
        while (sum[pos] > 0) {
            pos++;
        }

        while (--pos >= 0) {
            printf("%c", sum[pos]);
        }
        printf("\n");

    return 0;
}
