#include <stdio.h>

int main()
{
    int n;
    scanf("%d\n", &n);
    while(n-- > 0) {
        char * buff = NULL;
        size_t sz;
        int read = getline(&buff, &sz, stdin);
        char * p = buff;
        char stack[256];
        char * sPtr = stack; 
        int good = 1;
        /* printf("buff '%s' read %d \n", buff, read );  */
        if(read < 0) break;
        while(*p != '\0') {
            /* printf("*p %c sPtr %c\n",*p, *sPtr); */
            if(*p == ']' || *p == ')') {
                if(sPtr == stack) { 
                    good = 0;
                    break;
                }
                --sPtr;
                if( (*p == ']' && *sPtr != '[') ||
                    (*p == ')' && *sPtr != '(') ) {
                    good = 0;
                    break;
                }
            }
            else if(*p == '(' || *p == '[') {
                *sPtr = *p; 
                sPtr++;
            }

            p++;
        }
        if(sPtr != stack) good = 0;
        if(good) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
