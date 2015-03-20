#include<stdio.h>
#include <stdlib.h>

#define MAXI 30001
int M[] = {10, 5, 2, 1};
char A[MAXI + 1][4][30] = {{{0}}};
char *zero = "0";
char *one = "1";

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


char * find_val(int x, int lvl) 
{
    char * count = zero;
    int mul = M[lvl];
    if( mul <= x ) count = A[x-mul][lvl];

    if(lvl < 3)
        sumNumbers(A[x][lvl], count, find_val(x, lvl + 1));
    else 
        sumNumbers(A[x][lvl] , count , one);

    return A[x][lvl];
}

void printBackwards(char * res) {
    char * ptr = res;
    while(*ptr) ptr++;        /* seek to the end of the string */
    while(--ptr >= res) {   /* backwards walk to print string backwards */
        printf("%c", *ptr); 
    }
}

int main()
{
    int i;
    for (i = 0; i < MAXI+1; i++) {
        find_val(i, 0);
        /*
        printf("%d-%d: ", i*5, (i+1)*5-1); 
        printBackwards(A[i][0]); printf(" "); 
        printBackwards(A[i][1]); printf(" "); 
        printBackwards(A[i][2]); printf(" "); 
        printBackwards(A[i][3]); printf("\n"); 
        */
    }

    int p;
    while(scanf("%d\n", &p) != EOF) {
        char * res = A[p/5][0];
        if(res[0] == '1' && res[1] == '\0')
            printf("There is only 1 way to produce %d cents change.\n", p);
        else {
            printf("There are ");

            printBackwards(res);

            printf(" ways to produce %d cents change.\n", p);
        }
    }

    return 0;
}
