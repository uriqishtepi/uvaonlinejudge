#include<stdio.h>
#include<sys/param.h>

int rectangleSum(int arr[100][100][100], int n, int x, int y, int w, int z)
{
    int sum = 0;
    int i;
    for(i = 0; i <= w; i++) {
        sum += arr[z][x+i][y];
    }
    /* printf("rs %d %d %d %d  %d\n", x,y,w,z, sum); */
    return sum;
}

/* will get the max from point x,y 
 * if a rectangleSum is negative we should not continue 
 * the search from this x,y 
 */
int getMax(int arr[100][100][100], int n, int x, int y)
{
    /* printf("getMax(...,%d,%d,%d\n",n,x,y); */
    int maxEl = -100000000;
    int i;
    int j;
    int sofar[100] = {0};
    for(i = 0; i < n-x; i++) {
        for(j = 0; j < n-y; j++) {
            int sum = sofar[j]; 
            /*printf("rs %d %d %d %d  %d+%d->%d\n", x,y,i,j, sum, arr[j][x+i][y], sum+arr[j][x+i][y]);*/
            sum += arr[j][x+i][y];
            sofar[j] = sum;
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
        int k;
        int arr[100][100][100]; /* = {0}; */
        int maxEl = -10000000;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                int el;
                scanf("%d", & el);
                maxEl = MAX(maxEl, el);
                arr[0][i][j] = el;
                /* if j < 1, will not get in next loop */
                for(k = 1; k <= j; k++) {
                    arr[k][i][j-k] = arr[k-1][i][j-k] + el;
                }
            }
        }

        /*
        for(k = 0; k < n; k++) {
            for(i = 0; i < n; i++) {
                for(j = 0; j < n; j++) {
                    printf("%2d ", arr[k][i][j]);
                }
                printf("\n");
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
