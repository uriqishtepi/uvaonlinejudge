#include<stdio.h>
#include <string.h>
#include <stdlib.h>
int countInversions(int L[], int nitems)
{
    int swaps = 0;
    int i, j;
    for(i = 0; i < nitems-1; i++) {
        for(j = i+1; j < nitems; j++) {
            if(L[i] < L[j]) swaps++;
        }
    }
    return swaps;
}
int main()
{
    int n;
    scanf("%d\n",&n);
    int ncount = 0;
    char * buff = NULL;
    size_t nred;
    while(ncount++ < n) { 
        int nitems;
        scanf("%d\n",&nitems);
        /* printf("%d: has %d wagons ", ncount, nitems); */
        int nitemsOrig = nitems;

        int L[51] = {0};
        int swaps = 0;
        if(nitems > 0) { 
            getline(&buff, &nred, stdin);
            char * tok = strtok(buff, " \n");
            while(nitems-- > 0 && tok) {
                int val = atoi(tok);
                L[nitems] = val;
                tok =  strtok(NULL, " \n");
            }
            swaps = countInversions(L, nitemsOrig);
        }
        /* what if the line has 0 items, does it have a blank line */
        printf("Optimal train swapping takes %d swaps.\n", swaps);
    }
    return 0;
}
