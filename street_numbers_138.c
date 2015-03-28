#include<stdio.h>

int test(int i) 
{
printf("test i %d\n", i);
    int sum = ((1 + i) * i) /2;
    int d = 2 *sum + i*i - i;
    
    /* bin srch for L:
       L^2 + L -i^2 +i = 2*sum
       L > i
       so L ^2 + L = L*(L+1)= 2*sum +i^2 - i
    */

    int min = i;
    int max = sum;
    int mid = (min + max) / 2;
    while(min < max && mid != min && mid != max) {
/*printf("search i %d min %d max %d mid %d\n", i, min, max, mid); */
        int P = mid*(mid+1);
        if(P == d) {
            printf("%d %d\n", i, mid);
            return 1;
        }
        else if (P > d) {
            max = mid;
        }
        else {
            min = mid;
        }
        mid = (min + max) / 2;
    }
    
    return 0;
}

int main () 
{
    int i = 5;
    int counter = 0;
    while(counter < 10) {
        i++;
        if(test(i)) counter++;
    }
    return 0;
}
