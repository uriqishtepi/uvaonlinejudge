/* find sums of two very long integers input in column format */

#include<stdio.h>
#include <string.h>

char N[1000002];


void printBackwards(char * res) {
    char * ptr = res;
    while(*ptr) ptr++;        /* seek to the end of the string */
    while(--ptr >= res) {   /* backwards walk to print string backwards */
        printf("%c", *ptr); 
    }
}

/* sum c2 onto c1 */
unsigned char addDigit(char *c1, char c2, unsigned char carry)
{
    *c1 += c2 + carry;

    if(*c1 > '9') { 
        *c1 -= 10;
        return 1;
    } 
    return 0;
}

/* sum in place -- addend is much shorter than N
 * usually only one digit */
void sumToNumber(char * N, char * addend)
{
    char *p1 = N;
    char *p2 = addend;
    unsigned char carry = 0;

    while(*p2) {
        carry = addDigit(p1, (*p2) - '0', carry);
        p1++;
        p2++;
    }

    while(*p1 && carry) {
        carry = addDigit(p1, 0, carry);
        p1++;
    }

    if(!(*p1) && carry) 
        *p1++ = '1';
}


int main() 
{
    int num = 0;
    scanf("%d", &num);
    while(--num >= 0) {
        int digits = 0;
        scanf("%d", &digits);
        int offset = sizeof(N) - 2;
        while(--digits >= 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            /* printf("%d: %d %d\n", digits, a, b); */
            N[offset] = a+'0';
            N[offset-1] = '\0';
            char addend[2] = {0};
            addend[0] = b+'0';
            /*printf("a "); printBackwards(&N[offset]);printf("\n");*/
            sumToNumber(&N[offset], addend);
            /*printf("b "); printBackwards(&N[offset]);printf("\n"); */
            offset--;
        }

        printBackwards(&N[offset+1]);printf("\n"); 
        if(num > 0) printf("\n");
    }
    return 0;
}
