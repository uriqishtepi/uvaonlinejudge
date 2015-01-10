#include<stdio.h>

int main()
{
    unsigned int n;
    while(scanf("%u\n", &n) != EOF && n != 0) {
        int nstat = 1; /* 1-st walk */
        int rt = sqrt(n);
        if(rt*rt == n) printf("yes\n");
        else printf("no\n");
    }


    return 0;
}
