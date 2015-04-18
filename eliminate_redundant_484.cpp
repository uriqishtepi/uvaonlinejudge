#include<vector>
#include<map>
#include<stdio.h>

#define vi std::vector<int>
#define mi std::map<int, int>

int main()
{
    vi v;
    mi m;

    int n;
    while(scanf("%d", &n) != EOF) {
        mi::iterator it = m.find(n);
        if(it == m.end()) {
            m.insert(std::make_pair(n, 1));
            v.push_back(n);
        }
        else it->second++;
    }
    for(vi::iterator it = v.begin(); it != v.end(); ++it) {
        printf("%d %d\n", *it, m[*it]);
    }

    return 0;
}
