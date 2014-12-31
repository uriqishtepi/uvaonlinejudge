#include<stdio.h>

int main()
{
    int c;
    scanf("%d\n",&c);
    while(c > 0) {
        int n;
        scanf("%d\n",&n);
        int i = 0;
        double sum = 0;
        int arr[1000] = {0};

        for(i = 0; i < n; i++) {
            scanf("%d\n",&arr[i]);
            sum += arr[i];
        }

        double avg = sum / n;
        double above = 0;
        for(i = 0; i < n; i++) {
            if(arr[i] > avg) 
                above++;
        }
        printf("%.3lf\%\n", 100*above/n);
        c--;
    }
    return 0;
}
