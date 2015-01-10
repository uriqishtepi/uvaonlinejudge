#include<map>
#include<queue>
#include<set>
#include<vector>
#include<stdio.h>
#include<assert.h>
#define si std::set<int>
#define vi std::vector<int>
#define graph std::map<int, vi>
#define pq std::queue<int>

int main()
{
    int nodes;
    while(scanf("%d\n", &nodes) != EOF && nodes > 0) {
        assert(nodes <= 200);
        int colors[200] = {0};

        graph g;

        int edges;
        scanf("%d\n", &edges);
        int i;
        for(i=0;i<edges;i++) {
            int from, to;
            scanf("%d %d\n", &from, &to);
            g[from].push_back(to);
            g[to].push_back(from);
        }

        /* start at a node */
        si s;
        s.insert(g.begin()->first);
        int color = 1;
        colors[g.begin()->first] = color;
        bool good = true;
        
        while(!s.empty() && good == true) {
            if(color == 1) color = 2;
            else color = 1;
            si news;
            for(si::iterator it = s.begin(); good == true && it != s.end(); it++) {
                int from = *it;
                graph::iterator git = g.find(from);
                assert(git != g.end());
                for(vi::iterator vit = git->second.begin(); vit != git->second.end(); vit++) {
                    int to = *vit;
                    if(colors[to] > 0 && colors[to] != color) {
                        good = false;
                        break;
                    }
                    if(colors[to] < 1) news.insert(to);
                    colors[to] = color;
//printf("from %d to %d col[%d] %d , color %d\n", from, to, to, colors[to], color);
                }
            }
            s = news;
        }
        if(good) printf("BICOLORABLE.\n"); 
        else printf("NOT BICOLORABLE.\n"); 
    }
    return 0;
}
