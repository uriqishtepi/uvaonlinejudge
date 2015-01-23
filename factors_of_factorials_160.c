#include<stdio.h>


int main()
{
    int n;
    //find_first_fact()
    int fact[100];
    int fptr = 0;
    fact[fptr++] = 2;
    fact[fptr++] = 3;
    fact[fptr++] = 5;
    fact[fptr++] = 7;

    int j;
    int i;
    for(i = 11; i < 100; i++) {
        int fac = 1;
        for(j = 0; j < fptr; j++) {
            if((i % fact[j]) == 0) {
                fac = 0;
                break;
            }
        }
        if(fac) fact[fptr++] = i;
    }

    /*
    for(j = 0; j < fptr; j++) printf("%d ", fact[j]);
    printf("\n");
    */

    while(scanf("%d\n", &n) != EOF && n != 0) {
        if(n > 100) continue;
        if(n < 2) continue;
        int arr[100] = {0};
        for(i = n; i > 0; i--) {
            int val = i;
            for(j = 0; j < fptr; j++) {
               int f = fact[j];
               while(val > 1 && (val % f) == 0) {
                   arr[j]++;
                   val /= f;
               }
            }
        }
        printf("%3d! =", n);
        for(j = 0; j < fptr && fact[j] <= n; j++) {
            printf("%3d", arr[j]);
        }
        printf("\n");

    }

    return 0;
}
