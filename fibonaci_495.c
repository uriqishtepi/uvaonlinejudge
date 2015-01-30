#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/param.h>

inline unsigned char addDigit(char c1, char c2, char * c3, unsigned char carry)
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
    char F[5001][1047] = {{"0"}, {"1"}, {"1"}, {0}};
    int i;
    
    for(i=3;i<=5000;i++) {
        sumNumbers(F[i], F[i-1],F[i-2]);
    }
    int n;
    while(scanf("%d\n", &n) != EOF) {
        printf("The Fibonacci number for %d is ", n);
        int l = strlen(F[n]);
        char * p = F[n] + l - 1;
        while(p >= F[n]) printf("%c", *p--);
        printf("\n");
    }
    return 0;
}
