#include<stdio.h>


int main()
{
    int T;
    scanf("%d\n", &T);
    int N;
    while(--T >= 0 && scanf("%d\n", &N) != EOF) {
        char arr[3650] = {0};
        int P;
        scanf("%d\n", &P);
        int k;
        while(--P >= 0 && scanf("%d\n", &k) != EOF) {
            int i;
            for(i = k-1; i < N; i+=k)
                arr[i] = 1;
        }
        int days = 0;
        {
            int i;
            /*
            for(i = 0; i < N; i++)
                printf("%d ", arr[i]);
            printf("\n"); */

            for(i = 0; i < N; i++) {
                int d = i + 1;
                int q = d % 7;
                if(arr[i] && !(q == 0 || q == 6)) 
                    days++;
            }
        }
        printf("%d\n", days);
    }


    return 0;
}
