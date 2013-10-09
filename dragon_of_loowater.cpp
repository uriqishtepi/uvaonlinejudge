#include<stdio.h>
#include<vector>
#include<map>
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define si std::map<int, int>
int main()
{
    int nheads = 0;
    int nknights = 0;

    while(EOF != scanf("%d %d\n", &nheads, &nknights) && 
            nheads != 0 && nknights != 0) 
    {
        if(nheads > nknights) {
            printf("Loowater is doomed!\n");
            int d = 0;
            forl(i, 0, nheads) scanf("%d\n",&d);
            forl(i, 0, nknights) scanf("%d\n",&d);
            continue;
        }
        vi heads;
        heads.reserve(20000);
        forl(i, 0, nheads) {
            int d = 0;
            scanf("%d\n",&d);
            heads.push_back(d);
        }

        si knights;
        forl(i, 0, nknights) {
            int d = 0;
            scanf("%d\n",&d);
            knights[d] += 1;
        }

        long long min = 0;
        bool solvable = true;
        for(vi::iterator it = heads.begin(); it!=heads.end(); ++it) {
            si::iterator jt = knights.lower_bound(*it);
            if(jt == knights.end()) {
                solvable = false;
                break;
            }

            min += jt->first;
            if(--jt->second == 0)
                knights.erase(jt);
        }
        if(solvable)
            printf("%d\n", min);
        else
            printf("Loowater is doomed!\n");
    }
    return 0;
}
