#include<stdio.h>
#include<string.h>

int main()
{
    size_t nz;
    char * buff= NULL;
    char arr[101][101]={{'\0'}};
    int linecount = 0;
    int maxn =0;
    int i;
    int j;
    /*
    for(i=0; i <= 100;i++) {
        for(j=0; j <= 100;j++) 
            arr[i][j]=' ';
    }
    */

    while(getline(&buff,&nz,stdin) >=0) {
        int n = strlen(buff);
        if(buff[n-1] == '\n') n--;
        linecount++;
        for(i=0; i<n; i++) {
            arr[i][100 - linecount]=buff[i];
        }
        if(n > maxn) maxn = n;
        for(; i < maxn; i++) {
            arr[i][100 - linecount]=' ';
        }
    }

    /*
    for(i=0; i <= 100;i++) {
        printf("'");
        for(j=0; j <= 100;j++) 
            printf("%c", arr[i][j]);
        printf("'\n");
    }
    */

    for(i=0; i < maxn;i++) {
        printf("%s\n", &arr[i][100 - linecount]);
    }
    /*
    */

    return 0;
}

