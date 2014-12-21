#include <stdio.h>
int main ()
{
    char * buff = NULL;
    size_t n;
    int count;
    while((count = getline(&buff, &n, stdin)) > 0) {
        size_t i;
        int wcount = 0;
        int inword = 0;
        for(i = 0; i < count && buff[i] != '\n'; i++) {
            char c = buff[i];
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                inword = 1;
            else if(inword) {
                wcount++;
                inword = 0;
            }
        }
        printf("%d\n", wcount);
    }
    return 0;
}
