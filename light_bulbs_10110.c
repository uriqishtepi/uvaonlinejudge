#include<stdio.h>

int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF && n != 0) {
    /* for(n = 1; n < 300; n++) {  */
        int nstat = 1; /* 1-st walk */
        /*
        int i;
        for(i = 2; i <= n; i++) {
            if(n%i == 0) nstat = !nstat;   
        }
        printf("%d ", n);
        if(nstat) printf("yes\n");
        else printf("no\n");
        */


        /* printf("%d ", n); */
        int rt = sqrt(n);
        if(rt*rt == n) printf("yes\n");
        else printf("no\n");
        /*
        */
    }


    return 0;
}
