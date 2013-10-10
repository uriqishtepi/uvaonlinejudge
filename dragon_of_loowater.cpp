#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<set>
#include<map>
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define msi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define mi std::map<int, int>
#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif
int main(int argc, char **argv)
{
    int nheads = 0;
    int nknights = 0;

    out("Starting...\n");
    while(EOF != scanf("%d %d\n", &nheads, &nknights) && 
            nheads != 0 && nknights != 0) 
    {
        out("nheads = %d nknights = %d\n", nheads, nknights);
        if(nheads > nknights) {
            out("Got more heads than knights\n");
            printf("Loowater is doomed!\n");
            int d = 0;
            forl(i, 0, nheads) scanf("%d\n",&d);
            forl(i, 0, nknights) scanf("%d\n",&d);
            continue;
        }

        int min = 0;
        msi heads;
        out("heads\n");
        forl(i, 0, nheads) {
            int d = 0;
            scanf("%d\n",&d);
            out("d=%d\n",d);
            heads.insert(d);
        }

        out("knights\n");
        forl(i, 0, nknights) { 
            int d = 0;
            scanf("%d\n",&d);
            out("d=%d\n",d);
            if(!heads.empty()) {
                msi::iterator it = heads.lower_bound(d);
                if(it != heads.end()) { //we can get rid of exact values immediately
                    out("found, erasing from heads d=%d *it=%d\n",d, *it);
                    heads.erase(it);
                    min += d;
                }
            }
        }

        if(heads.empty())
            printf("%d\n", min);
        else
            printf("Loowater is doomed!\n");
    }
    return 0;
}
