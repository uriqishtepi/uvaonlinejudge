#include<stdio.h>
#include<string.h>

int main()
{
    char str[256];
    while(scanf("%s\n", str) != EOF && strncmp(str, "0", 256) != 0) {
        int len = strnlen(str, 256);
        int i;
        int order = 2;
        int sum = 0;
        for(i = len-1; i >= 0; i--, order *= 2) {
            int d = str[i] - '0';
            int dv = d * (order - 1);
            /* printf("adding %d\n", dv); */
            sum += dv;
        }
        printf("%d\n", sum);

    }

    return 0;
}
