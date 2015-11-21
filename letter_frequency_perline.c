#include<stdio.h>
#include<string.h>
#include<sys/param.h>

int main()
{
    char * str = NULL;
    int n;
    while(getline(&str, &n, stdin) > 0) {
        int arr[256] = {0};
        int len = strlen(str);
        int mx = 0;
        int i;
        for( i = 0; i < len; i++) {
            if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') )
            arr[str[i]]++;
            mx = MAX(mx, arr[str[i]]);
        }
        int l;
        for(l = 0; l < 256; l++) { 
            if(arr[l] > 0)
                printf("%c:%d ", l, arr[l]);
        }
        printf("\n");
            
    }

    return 0;
}
