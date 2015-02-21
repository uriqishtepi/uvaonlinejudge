#include<stdio.h>

int main()
{
    int T = 0;

    int counter = 0;
    scanf("%d\n", &T);
    while(++counter <= T) {
        int N = 0;
        int curr = 0;
        int last = 0;
        int hi = 0;
        int low = 0;
        scanf("%d ", &N);
        scanf("%d ", &last);
        while(--N > 0) {
            scanf("%d ", &curr);
            int diff = curr - last;
            if(diff > 0) hi++;
            else if(diff < 0) low++;
            last = curr;
        }
        printf("Case %d: %d %d\n", counter, hi, low);
    }


    return 0;
}
