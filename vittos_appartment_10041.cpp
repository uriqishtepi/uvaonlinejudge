#include<vector>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>

#define vi std::vector<int>

int getDist(vi & a, int pt)
{
    int dist = 0;
    for(vi::iterator it = a.begin(); it != a.end(); it++) {
        dist += abs(pt - *it);
    }
    return dist;
}

int main()
{
    int n;
    scanf("%d\n", &n);
    while(n-- > 0) {
        int r;
        scanf("%d\n", &r);
        vi a;
        int s;
        int count = 0;
        while(count++ < r) {
            scanf("%d ", &s);
            //printf ("%d ", s);
            a.push_back(s);
        }
        std::sort(a.begin(), a.end());
        int med = a[(r-1)/2];
        int dist = getDist(a, med);
        int dist2 = getDist(a, med+1);
        dist = std::min(dist, dist2);
        //printf("med %d dist %d\n", med, dist);
        printf("%d\n", dist);
    }

    return 0;
}   
