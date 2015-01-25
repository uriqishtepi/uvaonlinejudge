#include<stdio.h>
#include<string.h>
#include<sys/param.h>

int main()
{
    char * str = NULL;
    int n;
    while(getline(&str, &n, stdin) != EOF) {
        int arr[256] = {0};
        int len = strlen(str);
        int mx = 0;
        int i;
        for( i = 0; i < len; i++) {
            if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') )
            arr[str[i]]++;
            mx = MAX(mx, arr[str[i]]);
        }
        for( i = 'A'; i <='Z'; i++) 
            if(arr[i] >= mx) printf("%c", i);
        for( i = 'a'; i <='z'; i++) 
            if(arr[i] >= mx) printf("%c", i);
        printf(" %d\n", mx);
    }

    return 0;
}
