#include<vector>
#include<algorithm>
#include<stdio.h>

int main()
{
    int m;
    int count;
    std::vector<int> myv;
    while(scanf("%d\n", &m) != EOF) {
        myv.insert(std::lower_bound(myv.begin(), myv.end(),m), m);
        int sz = myv.size();
        if(sz & 0x1) { //odd
            printf("%d\n", myv[sz/2]);
        }
        else {
            int mid = (sz-1)/2;
            printf("%d\n", (myv[mid] + myv[mid+1]) / 2);
        }

    }
    return 0;
}
