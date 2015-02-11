#include<stdio.h>

int main()
{
    int n;
    int i = 0;
    scanf("%d\n", &n);
    char * buff = NULL;
    int sz;
    while(i++ < n && getline(&buff, &sz, stdin) >= 0) {
        char * tok = strtok(buff, " \n");
        int max = -1;
        while (tok != NULL) {
            int n = atoi(tok);
            if(max < n) max = n;

            tok = strtok(NULL, " \n");
        }
        printf("Case %d: %d\n", i, max);
    }

    return 0;
}
