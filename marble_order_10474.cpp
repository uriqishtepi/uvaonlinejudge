#include <vector>
#include <algorithm>
#include <stdio.h>

#define vi std::vector<int> 

int main ()
{
    int N, Q;
    int counter = 0;
    while (scanf("%d %d", &N, &Q) != EOF && !(N == 0 && Q == 0)) {
        vi arr(N);
        int r;
        int i;
        for(i = 0; i < N; i++)
        {
            scanf("%d", &r);
            arr[i] = r;
        }

        std::sort(arr.begin(), arr.end());
        printf("CASE# %d:\n", ++counter);

        for(i = 0; i < Q; i++)
        {
            scanf("%d", &r);
            vi::iterator it = std::find(arr.begin(), arr.end(), r);
            if(it == arr.end())
                printf("%d not found\n", r);
            else
                printf("%d found at %d\n", r, it - arr.begin() + 1);
        }

    }
    return 0;
}
