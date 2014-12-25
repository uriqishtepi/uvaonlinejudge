#include<stdio.h>
#include <string.h>
#define MAXL 100

int charstrAdd(char a[MAXL], char b[MAXL])
{
    int s = 0;
    char carry = 0;
    while(s < MAXL && a[s] > 0) {
        char sum = a[s] + b[s] + carry - 2 * '0';
        if(sum >= 10) {
            sum -= 10;
            carry = 1;
        }
        else carry = 0;
        b[s] = sum + '0';
        s++;
    }
    if(carry > 0 && s < MAXL) b[s] = '1';

    if(s >= MAXL) 
        return -1;
    else
        return 0;
}


void reverse(char a[MAXL], char b[MAXL])
{
    memset(b, 0, MAXL);
    int len = strnlen(a, MAXL);
    int i;
    for(i = 0; i < len; i++) {
        b[len-i-1] = a[i];
    }
}

void process(char * str)
{
    int count = 0;
    char str1[MAXL];
    char str2[MAXL];
    strncpy(str2, str, MAXL);
    do {
        reverse(str2, str1); /* result in second parameter */
        if(strncmp(str1, str2, MAXL) == 0) {
            printf("%d %s\n", count, str1);
            return;
        }
        int rc = charstrAdd(str1, str2); /* result in second parameter */
        if(rc) break;
    } while(++count < 1000);
    printf("No solution for %s\n", str);
}

int main()
{
    unsigned int n;
    char str1[MAXL] = {0}; /* "2345678"; */
    /* char str2[MAXL];
    reverse(str1,str2); //result in str2
    printf("%s + %s ", str1, str2);
    charstrAdd(str1, str2); //result in str2
    printf("= %s \n", str2);
    return; */
    scanf("%u\n", &n);
    while(n-- > 0) {
        scanf("%s\n", str1);
        /* printf("%d\n", n); */
        process(str1);
    }
}
