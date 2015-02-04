/*
4 6 8 5 ->
8 6 4 5 -> 5 4 6 8 -> 4 5 6 8
5 8 6 4 -> 6 8 5 4 -> 8 6 5 4 -> 4 5 6 8

1 2 3 4 6 8 5
smallest moves: 5 8 6 4 3 2 1 -> 6 8 5 4 3 2 1 -> 8 6 5 4 3 2 1 ->1 2 3 4 5 6 8
also valid :    8 6 4 3 2 1 5 -> 5 1 2 3 4 6 8 -> 4 3 2 1 5 6 8 ->1 2 3 4 5 6 8


keep going until delta is with the same sign, when delta flips

5 1 2 3 4 -> 

in two flips can find the max and put it at the end, recurse (1, n-1), ~2n flips
*/
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

/* returns position of max */
int find_max(int arr[30], int items) 
{
    int j;
    int max = 0;
    for(j=1; j < items; j++) {
        if(arr[max] < arr[j]) max = j;   
    }
    return max;
}

/* returns position of max */
void flip(int arr[30], int pos) {
    int * p1 = arr;
    int * p2 = &arr[pos];
    while(p1 < p2) {
        int t = *p1;
        *p1 = *p2;
        *p2 = t;
        p1++;
        p2--;
    }
}

void printArr(int arr[30], int count) 
{
    if(count < 1) return;
    printf("%d", arr[0]);   
    int i;
    for(i=1;i<count;i++) {
        printf(" %d", arr[i]);   
    }
    printf("\n");
}


int main()
{
    char * buff = NULL;
    size_t nz;
    while(getline(&buff, &nz, stdin) >= 0) {
        char * tok = strtok(buff, "\n ");
        int count = 0;
        int arr[30] = {0};
        while(tok) {
            arr[count] = atoi(tok);
            count++;
            tok = strtok(NULL, "\n ");
        }

        printArr(arr, count);

        int n;
        for(n = count; n > 0; n--) { /*how many pieces to look at */
            int max = find_max(arr, n); /* position of max */
//printf("max %d %d count %d\n", max, arr[max], count);
            if(max == n - 1) 
                continue; /*already at it's place */
            if(max != 0) {
                flip(arr, max); /* put max at front */
                printf("%d ", count - max);
                //printArr(arr, count);
            }
            flip(arr, n - 1); /* put max at end */
            printf("%d ", count - n + 1);
            //printArr(arr, count);
        }
        printf("0\n");
    }
    return 0;
}
