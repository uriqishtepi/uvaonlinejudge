#include<stdio.h>
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
        *p3 = '0';
        *(++p3) = '\0';
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

int main() 
{

    char str1[512];
    char str2[512];

    int n;
    char res[1024] = {0};
    char tmp1[1024] = {0};
    char tmp2[1024] = {0};
    while(scanf("%s\n%s\n", str1, str2) != EOF) {
        if(str1[0] == '0' || str2[0] == '0') {
            printf("0\n");
            continue;
        }

        int l1 = strlen(str1);
        int l2 = strlen(str2);
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

        int i;
        for(i = 0; i < mn; i++) {
            mulDigit(tmp1, pmx, mx, pmn[i], mn - i - 1);
            sumNumbers(tmp2, res, tmp1);
            memcpy(res, tmp2, sizeof(tmp2));
            /* printf("%s %s\n", res[i], res[l2]); */
        }

        char * p = res + mx - 1;
        while(*p) p++;
        p--;
        while(p >= res) { printf("%c", *p); *p-- = '\0'; }
        *p-- = '\0';
        printf("\n");
    }

    return 0;
}
