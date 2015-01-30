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
        p3++;
    }

    char carry = 0;
    while(p1 >= str1) {
        char prod = (*p1 - '0') * (c2 - '0') + carry;
        carry = prod / 10; 
        *p3 = prod - (carry * 10) + '0';
        p1--;
        p3++;
    }
    if(carry) *p3 = carry + '0';
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
        *p3 = '1';
}

int main() 
{

    char str1[512];
    char str2[512];

    int n;
    while(scanf("%s\n%s\n", str1, str2) != EOF) {
        char res[512][512] = {{0}};

        int l1 = strlen(str1);
        int l2 = strlen(str2);
        int i;
        for(i = 0; i < l2; i++) {
            char tmp[512] = {0};
            mulDigit(res[i], str1, l1, str2[i], l2 - i - 1);
            sumNumbers(tmp, res[l2], res[i]);
            memcpy(res[l2], tmp, sizeof(tmp));
            /* printf("%s %s\n", res[i], res[l2]); */
        }

        char * p = res[l2];
        int l = 0;
        int izero = 1;
        while(*p) { if(*p != '0') izero=0; p++; l++; }
        if(izero) printf("0\n");
        else {
            p--;
            while(p >= res[l2]) printf("%c", *p--);
            printf("\n");
        }
    }

    return 0;
}
