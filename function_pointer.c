#include<stdio.h>

int blah(int a) 
{
    printf("called blah %d\n", a);
    return a+1;
}

int main()
{
    /* can call printf indirectly:  
     * void (*outFunc)(const char *fmt, ...) = printf;
     * outFunc("blah\n");
     */
    int (*fptr)(int) = NULL;

    if(fptr == NULL)
        fptr = blah;

    fptr(5);
    return 0;
}
