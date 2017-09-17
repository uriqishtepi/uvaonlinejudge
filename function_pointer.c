#include<stdio.h>

int blah(int a) 
{
    printf("called blah %d\n", a);
    return a+1;
}

int set_ptr(char **cptr)
{
    *cptr = "blah";
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

    char **cptr = NULL;
    set_ptr(cptr);
    printf("cptr = %s\n", cptr);

    return 0;
}
