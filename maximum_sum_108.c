#include<stdio.h>
#include<sys/param.h>

int main()
{
    int n;
    while(scanf("%d\n", &n) != EOF) {

        int i;
        int j;
        int h[100][100] = {0}; /* horiz max up to this el */
        int v[100][100] = {0}; /* vert max up to this el */
        int r[100][100] = {0}; /* rect max up to this el */
        int maxEl = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                int el;
                scanf("%d", &el);
                if(i == 0 && j == 0) { 
                    maxEl = el;
                }

                if(i > 0) {
                    int s = v[i-1][j] + el;
                    v[i][j] = s > 0 ? s : el;
                    maxEl = MAX(maxEl, v[i][j]);
                }
                else
                    v[i][j] = el;

                if(j > 0) {
                    int s = h[i][j-1] + el;
                    h[i][j] = s > 0 ? s : el;
                    maxEl = MAX(maxEl, h[i][j]);
                }
                else
                    h[i][j] = el;

                if(i > 0 && j > 0) {
                    int s = r[i-1][j-1] + h[i][j-1] + v[i-1][j] + el;
                    r[i][j] = s > 0 ? s : el;
                    maxEl = MAX(maxEl, r[i][j]);
                }
                else if(i > 0) 
                    r[i][j] = v[i][j];
                else if(j > 0)
                    r[i][j] = h[i][j];
                else
                    r[i][j] = el;
            }
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                printf("%d ", h[i][j]);
            }
            printf("\n");
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                printf("%d ", v[i][j]);
            }
            printf("\n");
        }

        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                printf("%d ", r[i][j]);
            }
            printf("\n");
        }
        printf("%d\n", maxEl);

    }

    return 0;
}
