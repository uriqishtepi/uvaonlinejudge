/* find if a number is divisible by 11
 * since it is hard to do division of long numbers, 
 * and since i had multiplication, i can multiply by 1/11
 * which is 0.9090909090, and find the quotient
 * then multiply back with 11 to check if we have a match.
 */

#include<stdio.h>
#include <stdlib.h>
#include<string.h>

/*  567
 * x  3
 * ----
 *   21
 *  18
 * 15
 * ----
 * 1701
 *
 * but backwards
 *  765
 *  3 x
 *  ---
 *  12
 *   81
 *    51
 *  ---
 *  i071
 *
 *
 *  so 
 *
 *  765
 *  32 x
 *  ---
 *  1071 +
 *  04311
 *
 * 555 -> [256][256][43]
 */
void mulDigit(char * res, char * str1, int l1, char c2, int skip)
{
    char * p1 = str1 + l1 - 1;
    char * p3 = res;
    while(skip-- > 0) {
        *p3++ = '0';
    }

    char carry = 0;
    while(p1 >= str1) {
        char prod = (*p1 - '0') * (c2 - '0') + carry;
        carry = prod / 10; 
        *p3++ = prod - (carry * 10) + '0';
        p1--;
    }
    if(carry) *p3++ = carry + '0';

    *p3 = '\0';
}

unsigned char addDigit(char c1, char c2, char * c3, unsigned char carry)
{
    *c3 = c1 + c2 + carry;

    if(*c3 > '9') { 
        *c3 -= 10;
        return 1;
    } 
    return 0;
}

void sumNumbers(char * res, char * num1, char * num2)
{
    char * p1 = num1;
    char * p2 = num2;
    char * p3 = res;
    unsigned char carry = 0;

    while(*p1 && *p2) 
        carry = addDigit(*p1++, (*p2++) - '0', p3++, carry);

    while(*p1) 
        carry = addDigit(*p1++, 0, p3++, carry);

    while(*p2) 
        carry = addDigit(*p2++, 0, p3++, carry);

    if(carry) 
        *p3++ = '1';

    *p3 = '\0';
}

int multiplyNumbers(char * res, char * str1, int l1, char * str2, int l2)
{
    int mx, mn;
    char *pmx, *pmn;
    if(l1 > l2) {
        mx = l1;
        mn = l2;
        pmx = str1;
        pmn = str2;
    }
    else {
        mx = l2;
        mn = l1;
        pmx = str2;
        pmn = str1;
    }

    char tmp1[2024] = {0};
    char tmp2[2024] = {0};

    int i;
    for(i = 0; i < mn; i++) {
        mulDigit(tmp1, pmx, mx, pmn[i], mn - i - 1);
        sumNumbers(tmp2, res, tmp1);
        memcpy(res, tmp2, sizeof(tmp2));
        /* printf("%s %s\n", res[i], res[l2]); */
    }

    char * p2 = res + mx - 1;
    char * p1 = res;
    while(*p2) p2++;      /* seek to the end of the string */
    size_t len = p2 - res;
    while(--p2 > p1) {  /* backwards walk to print string backwards */
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
    }
    return len;
}

void intdivbyeleven(char * str)
{
    int a = atoi(str);
    int quotient = a /11;
    if(quotient * 11 == a) {
            printf("%s is a multiple of 11.\n", str);
    }
    else {
            printf("%s is not a multiple of 11.\n", str);
    }
}

int main() 
{
    char str1[1001];
    char str2[1011];

    while(scanf("%s\n", str1) != EOF) 
    {
        int l1 = strlen(str1);
        if(str1[0] == '0' && l1 == 1) {
            break;
        }

        if(l1 < 8) {
            intdivbyeleven(str1);
            continue;
        }

        int i = 0;
        while(i <= (l1+1)/2) {
            str2[i++] = '9';
            str2[i++] = '0';
        }
        str2[i++] = '9';
        str2[i++] = '1';
        int l2 = i;

        char res[2024] = {0};
        int resl = multiplyNumbers(res, str1, l1, str2, l2);
        /* printf("long res %s  resl %d\n", res, resl); */
        int shortlen = resl - (l2 + 1);
        res[shortlen]='\0'; /* divide by 10^l2 */
        /*printf("short res %s  shortlen %d\n", res, shortlen); */
        
        char mulres[2024] = {0};
        char eleven[] = "11";
        multiplyNumbers(mulres, res, shortlen, eleven, 2);
        /*printf("mulres %s vs orig %s\n", mulres, str1); */
        if(strcmp(mulres, str1) == 0) {
            printf("%s is a multiple of 11.\n", str1);
        }
        else {
            printf("%s is not a multiple of 11.\n", str1);
        }
    }

    return 0;
}
