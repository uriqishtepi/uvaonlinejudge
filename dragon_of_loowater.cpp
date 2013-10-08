#include<stdio.h>
#include<vector>
#include<set>
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define si std::set<int>
int main()
{
    int nheads = 0;
    int nknights = 0;

    while(true) {
        scanf("%d %d\n", &nheads, &nknights);
        if(nheads == 0 && nknights == 0) 
            break;

        vi heads;

        forl(i, 0, nheads) {
            int d = 0;
            scanf("%d\n",&d);
            heads.push_back(d);
        }

        si knights;
        forl(i, 0, nknights) {
            int d = 0;
            scanf("%d\n",&d);
            knights.insert(d);
        }

        int min = 0;
        bool solvable = true;
        for(vi::iterator it = heads.begin(); it!=heads.end(); ++it) {
            si::iterator jt = knights.lower_bound(*it);
            if(jt == knights.end()) {
                solvable = false;
                break;
            }
            printf("for %d we found %d \n", *it, *jt);

            min += *jt;
            knights.erase(jt);
        }
        if(solvable)
            printf("%d\n", min);
        else
            printf("Loowater is doomed!\n");
    }
    return 0;
}
