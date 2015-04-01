#include<stdio.h>

int getStrHash(char * str)
{
    int c1 = 0;
    char * ptr;
    for(ptr=str; *ptr!='\0';ptr++)  {
        char c = *ptr;
        if('a'<= c && c <= 'z') c1+=c-'a' +1;
        if('A'<= c && c <= 'Z') c1+=c-'A' +1;
        if(c1 > 9) c1 = c1/10 + c1%10;
    }
    return c1;
}

int main()
{
    char *str1 = NULL;
    char *str2 = NULL;
    int sz1, sz2;

    while(getline(&str1, &sz1,stdin) > 0 && getline(&str2, &sz2,stdin) > 0)
    {
        int c1 = getStrHash(str1);
        int c2 = getStrHash(str2);
        /* printf("%s %d\n", str1, c1); printf("%s %d\n", str2, c2); */
        int min = c1;
        int max = c2;
        if(c1 > c2) {
            max = c1;
            min = c2;
        }
        printf("%.2f %%\n", 100.0 * min/max);

    }
    return 0;
}
