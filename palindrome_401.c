#include<stdio.h>
#include<assert.h>


int main()
{
char arr[256] = {0};
arr['A'] = 'A';
arr['E'] = '3';
arr['H'] = 'H';
arr['I'] = 'I';
arr['J'] = 'L';
arr['L'] = 'J';
arr['M'] = 'M';
arr['O'] = 'O';
arr['S'] = '2';
arr['T'] = 'T';
arr['U'] = 'U';
arr['V'] = 'V';
arr['W'] = 'W';
arr['X'] = 'X';
arr['Y'] = 'Y';
arr['Z'] = '5';
arr['1'] = '1';
arr['2'] = 'S';
arr['3'] = 'E';
arr['5'] = 'Z';
arr['8'] = '8';


    char str[10256];
    int n;
    while(scanf("%s%n\n", str, &n) != EOF) {
        int palindrome = 1;
        int symmetric = 1;
        assert(strlen(str) == n);
        char * b = str;
        char * e = str + n - 1;
        while(b <= e) {
            if(*b != *e)
                palindrome = 0;
            if(arr[*b] != *e) 
                symmetric = 0;
            b++; e--;
        }
        printf("%s -- ", str); 
        if(symmetric && palindrome)
            printf("is a mirrored palindrome.");
        else if(palindrome)
            printf("is a regular palindrome.");
        else if(symmetric)
            printf("is a mirrored string.");
        else
            printf("is not a palindrome.");
        printf("\n\n"); /* ose  \n \n  */
        /* printf("%s  --  %d%d\n\n", str, palindrome, symmetric); */
    }

    return 0;
}
