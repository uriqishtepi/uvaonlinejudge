#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


struct edge {
    int from;
    int to;
    int weight;
    bool operator<(const edge & other) {
        out("****** operrator < \n");
        return this->weight < other.weight;
    }
};

struct cmpedge {
    bool operator()(const edge & a, const edge &b) {
        return a.weight < b.weight;
    }
};




#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mii std::map<int, int>  //map int int
#define se std::set<edge, cmpedge>  //set of edges
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 200000000
#define MAXCIT 10000
#define MAXRD  100000


enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(se::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d-%d(%d), ", it->from, it->to, it->weight);
        }
        out("\n");
    }
}



//modified version of dijkstra's for our problem, 
//need to compute shortest paths from every node with
//a hotel, this means that we will start from all H
//cities at the same time.
void ModShortestPath(const graphtp & g, int h, int H[])
{
    int comparisons = 0;
    int size = g.size();
    vi visited(g.size());

    mii q; //map weight to nodeid
    q.insert(std::make_pair(0,0));

    int counter = 0;
    while(!q.empty()) 
    {
        //pop first
        int node = q.begin()->second;
        int nh = q.begin()->first % 1000;
        int nd = q.begin()->first / 1000;
        q.erase(q.begin());

        visited[node] = true;
        out("\n%d: popped %d (%d,%d) \n", counter++, node, nd, nh);

        if(node == size - 1) {
            out("RESULT: ");
            printf("%d\n", nd);
            return;
        }

        for(se::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
        {
            assert(it->from == node && "encountered an inconsistend element");
            out("considering %d -> %d (w %d)\n", node, it->to, it->weight);

            if(visited[it->to]) {
                out("encountered a prev. visited node %d\n", it->to);
                continue;
            }

            int nexth = nh + it->weight;
            if(nexth < 600) {
                
                out("\ninserting %d (%d,%d) \n", it->to, nd, nexth);
                q.insert(std::make_pair(nd*1000+nexth, it->to));
             }
            if( H[node] ) { //if it is not a hotel, nothing to do
                out("\nHinserting %d (%d,%d) \n", it->to, nd+1, it->weight);
                q.insert(std::make_pair((nd+1)*1000+it->weight, it->to));
            }

            //out("dist from %d to %d; old dist %.2f vs new dist %.2f\n", node, it->to, D[it->to], dist);
        }
    }
    out("RESULT: ");
    printf("-1\n");
}



int main(void)
{
  out("starting ...\n");
  int N; //number of cities
  int ord = 0;
    
  while(scanf("%d\n", &N) > 0 && N > 0) {
    assert(N >= 2 && N <= MAXCIT);
    out("N %d\n",N);
    graphtp g; //populate g with n empty nodes
    forl(i, 0, N) {
        g.push_back(se()); //g contains as many nodes as the number of cities
    }

    std::vector<int>D(MAXCIT*MAXCIT);
    int H[MAXCIT] = {0};

    int h = 0;
    scanf("%d ", &h);
    out("h=%d\n", h);
    assert(h < 100 && h < N);

    forl(i, 0, h) {
        int h;
        scanf("%d", &h);
        assert(h > 0 && h < MAXCIT);
        H[h] = 1;
        out("H[%d] = %d\n",i, H[i]);
    }

    int m = 0;
    scanf("%d ", &m);
    out("m = %d\n", m);
    assert(m <= MAXRD);
    

    forl(i, 0, m) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t); //from, to, time
        out("r[%d] = %d %d %d\n", i, a, b, t);
        assert(a >= 1 && a <= N); // start from 1
        assert(b >= 1 && b <= N); // start from 1
        assert(t >= 1 && t <= 600); // start from 1

        if(t > 600) continue;
        edge e;
        e.from = a-1;
        e.to = b-1;
        e.weight = t;
        g[e.from].insert(e);
        e.from = b-1;
        e.to = a-1;
        g[e.from].insert(e);
    }

    out("Case %d:\n", ++ord);
    print_graph(g);

    ModShortestPath(g, h, H);
  }

  return 0;
}
