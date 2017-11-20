/* after sorting by the weight increasing, we need to find 
 * longest decreasing subsequence for the q
 */
#include<stdio.h>
#define MAX 1000

int main()
{
    int cnt = 0;
    int w[MAX+1] = {0};
    int q[MAX+1] = {0};
    int order[MAX+1] = {0};
    while(scanf("%d %d", &w[cnt], &q[cnt]) != EOF) {
        printf("%d: %d %d %f\n", cnt+1, w[cnt], q[cnt], ((double) w[cnt])/q[cnt]);
        order[cnt] = cnt + 1;
        cnt++;
    }

    //order by w
    //then use that order to pick longest decreasing subsequence for q
    return 0;
}
