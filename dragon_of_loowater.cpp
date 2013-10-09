#include<stdio.h>
#include<iostream>
#include<algorithm>
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
        forl(i, 0, nheads) {
            int d = 0;
            scanf("%d\n",&d);
            heads.push_back(d);
        }

        vi knights;
        forl(i, 0, nknights) {
            int d = 0;
            scanf("%d\n",&d);
            knights.push_back(d);
        }

        std::sort(heads.begin(), heads.end());
        std::sort(knights.begin(), knights.end());

        long long min = 0;
        bool solvable = true;
        vi::iterator last = knights.begin();

        for(vi::iterator it = heads.begin(); it!=heads.end(); ++it) {
            //std::cout << "considering " << *it << std::endl;
            last = std::lower_bound(last, knights.end(), *it);
            //std::cout << "distance h " << distance(it, heads.end())<< std::endl;
            //std::cout << "distance k " << distance(last, knights.end())<< std::endl;

            if(last == knights.end() || heads.end() - it > knights.end() - last)
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
