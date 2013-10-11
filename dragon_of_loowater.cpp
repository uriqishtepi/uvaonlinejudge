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
    vi heads;
    vi knights;

    out("Starting...\n");
    while(EOF != scanf("%d %d\n", &nheads, &nknights) && 
            nheads != 0 && nknights != 0) 
    {
        out("nheads = %d nknights = %d\n", nheads, nknights);
        if(nheads > nknights) {
            out("Got more heads than knights\n");
            printf("Loowater is doomed!\n");
            int d = 0;
            char * temp = NULL;
            size_t n;
            forl(i, 0, nheads) getline(&temp, &n, stdin);

            forl(i, 0, nknights) getline(&temp, &n, stdin);
            continue;
        }

        int hmin = 2000000000;
        heads.clear();
        heads.reserve(20000);
        out("heads\n");
        forl(i, 0, nheads) {
            int d = 0;
            scanf("%d\n",&d);
            out("d=%d\n",d);
            heads.push_back(d);
            hmin = std::min(hmin, d);
        }
        //std::sort(heads.begin(), heads.end());

        knights.clear();
        knights.reserve(20000);
        out("knights\n");
        forl(i, 0, nknights) {
            int d = 0;
            scanf("%d\n",&d);
            out("d=%d\n",d);
            if(d >= hmin)
                knights.push_back(d);
        }        
        
        if(heads.size() > knights.size())
            printf("Loowater is doomed!\n");

        std::sort(knights.begin(), knights.end());
        vi::iterator last = knights.begin();
        
        int min = 0;
        bool solvable = true;
        for(vi::iterator it = heads.begin(); it != heads.end(); ++it) 
        { 
            out("considering %d ", *it);
            last = std::lower_bound(last, knights.end(), *it);
            if(last == knights.end()) {
                out("Not found \n");
                solvable = false;
                break;
            }
            out("found %d\n", *last);
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
