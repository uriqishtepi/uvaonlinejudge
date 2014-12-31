#include<stdio.h>
#include<sys/param.h>

int rectangleSum(int arr[100][100], int n, int x, int y, int w, int z)
{
    int sum = 0;
    int i;
    int j;
    for(i = 0; i <= w; i++) {
        for(j = 0; j <= z; j++) {
            sum += arr[x+i][y+j];
        }
    }
    /* printf("rs %d %d %d %d  %d\n", x,y,w,z, sum); */
    return sum;
}

int getMax(int arr[100][100], int n, int x, int y)
{
    int maxEl = -100000000;
    int i;
    int j;
    for(i = 0; i < n-x; i++) {
        for(j = 0; j < n-y; j++) {
            int sum = rectangleSum(arr, n, x, y, i, j);
            maxEl = MAX(maxEl, sum);
        }
    }
    return maxEl;
}

int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF) 
    {
        int i;
        int j;
        int arr[100][100] = {0}; 
        int maxEl = -10000000;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &arr[i][j]);
                maxEl = MAX(maxEl, arr[i][j]);
            }
        }

        /*
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                printf("%2d ", arr[i][j]);
            }
            printf("\n");
        }
        */



        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                int mx = getMax(arr, n, i, j);
                maxEl = MAX(maxEl, mx);
            }
        }
        printf("%d\n", maxEl);
    }

    return 0;
}
