#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define msi std::multiset<int>
#define si std::set<int>
#define mi std::map<int, itn>
//#define DEBUG true
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

        vi knights;
        out("knights\n");
        forl(i, 0, nknights) {
            int d = 0;
            scanf("%d\n",&d);
            out("d=%d\n",d);
            msi::iterator it = heads.find(d);
            if(it != heads.end()) { //we can get rid of exact values immediately
                out("found, erasing from heads d=%d\n",d);
                heads.erase(it);
                min += d;
            }
            else
                knights.push_back(d);
        }

        std::sort(knights.begin(), knights.end());

        bool solvable = true;
        vi::iterator last = knights.begin();

        for(msi::iterator it = heads.begin(); it != heads.end(); ++it) {
            out("considering %d\n", *it );
            last = std::lower_bound(last, knights.end(), *it);
            out("distance h %d\n", distance(it, heads.end()));
            out("distance k %d\n", distance(last, knights.end()));

            if(last == knights.end() || distance(it, heads.end()) > distance(last, knights.end()))
            {
                solvable = false;
                break;
            }

            min += *last;
            ++last;
        }

        if(solvable)
            printf("%d\n", min);
        else
            printf("Loowater is doomed!\n");
    }
    return 0;
}
