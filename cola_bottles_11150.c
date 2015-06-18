#include<stdio.h>

int main()
{
    int a[201] = {0};
    int wb[201] = {0}; /*without borrow */
    int rem[201] = {0}; /* orig remainder */
    int i = 0;
    
    for(i=1;i<200;i++) {
        int currem = i % 3;
        int q = i / 3;
        a[i] = i + wb[q];
        wb[i] = a[i];
        rem[i] = currem;
        if(currem + rem[q] > 1) { /* if 2 borrow one */
            a[i] += 1;
        }
        printf("%d: %d\n", i, a[i]);
    }
    /*
    int N;
    while(scanf("%d", &N) != EOF) { printf("%d\n", a[i]); }
    */

    return 0;
}
