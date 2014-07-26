#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


struct edge {
    int from;
    int to;
    float weight;
    bool operator<(const edge & other) {
        return this->weight < other.weight;
    }
} ;

struct cmpedge {
    bool operator()(const edge & a, const edge &b) {
        return a.weight < b.weight;
    }
};


#define vi std::vector<int>
#define mwp std::map<float, edge> //map weight and destination point 
#define graphtp std::vector< mwp >  //graph is a vector of maps -- the edges
#define pqtp std::set< edge, cmpedge >  //priority que

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(unsigned int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(mwp::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d(%f), ", it->second.to, it->second.weight);
        }
        out("\n");
    }
}


inline int findroot(vi &uf, int node)
{
    int parent = uf[node];

    while(uf[parent] != parent) //we found the root, its parent
    {
        uf[node] = uf[parent]; //path compression to only the parent
        node = parent; //load next parent
        parent = uf[parent];
    }

    return parent; //finally root of the tree

}

//
// perform union-find procedure in one go
// traverse tree upwards until we find the root of the tree
// we need to know the weights too, so we merge the smaller tree
// into the larger one, by setting the parent of the smaller tree 
// to be the root of the larger one.
// if the union was successful we return true
// if the two elements were already in the same tree, return false
//
bool unionfind(vi & uf, int a, int b)
{
    int parent_a = findroot(uf, a);
    int parent_b = findroot(uf, b);

    if(parent_b == parent_a)
        return false;

    //randomly pick a to be the root of both trees
    uf[parent_b] = parent_a;
    return true;
}





//
// minimum spanning tree, Kruskal
// start from the smallest weight edge, and join vertices in a tree, 
// as long as there is no cycle (ie both terminals in the same tree)
// to achieve that we need a set indicating each subtree, and merge
// the two corresponding sets when extracting an edge that joins two vertices.
// the union find mechanism works well and performs almost constant
float MST(const graphtp & g, pqtp & pq)
{
    vi uf(g.size()); //union find structure
    int visited = 0;
    float totpath = 0.0;

    //for each vertex need a set
    for(int n = 0; n < g.size(); n++)
        uf[n] = n;

    pqtp::iterator it = pq.begin();
    while(it != pq.end() && visited < g.size()) {
        edge e = *it; //extract min
        pq.erase(it++);

        //unionfind will return false if they are in the same tree
        if(false == unionfind(uf,e.to,e.from)) 
            continue;
        
        //process this edge
        printf ("%d - %d (%f)\n", e.from, e.to, e.weight);
        totpath += e.weight;
        visited++;
    }
    return totpath;
}

//minimum spanning tree, prim's version, keeping it here for reference
float MST_Prims(const graphtp & g)
{
    vi visited(g.size());
    mwp globl;
    float totpath = 0;

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;
        
        //start with current in queue
        std::queue<int> q;
        globl.insert(g[n].begin(),g[n].end());
        out("length of globl %d\n", globl.size());

        visited[n] = true;
        out("initial n %d ", n);

        int counter = 0;
        while(!globl.empty()) 
        {
            //pop first
            edge e = globl.begin()->second;
            globl.erase(globl.begin());
            if(visited[e.to])
                continue;

            visited[e.to] = true;
            printf("%d - %d (%f)\n", e.from, e.to, e.weight);
            totpath += e.weight;

            out("\n%d: popped %d \n", counter++, e.to);

            for(mwp::const_reverse_iterator it = g[e.to].rbegin(); it != g[e.to].rend(); ++it)
            {
                out("considering %d -> %d \n", e.to, it->second.to);
                if(visited[it->second.to]) {
                    out("encountered a prev. visited node %d\n", it->second.to);
                    continue;
                }
                globl.insert(*it);
            }
        }
    }
    
    return totpath;
}



int main(int argc, char**argv)
{
  out("starting ...\n");
  std::cout << " Kruskal MST (min spanning tree) " << std::endl;
  if(argc > 1 && strncmp(argv[1], "-d", 3))
    int g_debug = 1;

  int N; //test cases
  scanf("%d\n", &N);
  out("N %d\n",N);
  int ord = 0;
    
  //for Kruskal I used list of edges-weights format
  while(N-- > 0) {
    char * buff = NULL;
    graphtp g;
    pqtp pq;
    int counter = 0;

    int cn; //count of nodes
    int ce; //count of edges
    scanf("%d %d\n", &cn, &ce); 
    out("cn %d ce %d\n", cn, ce); 


    for(int i = 0; i < cn; ++i) {
        mwp me;
        g.push_back(me);
    }

    int i = 0;
    while(i++ < ce) 
    {
        int nodefrom;
        int nodeto;
        float weight;
        scanf("%d %d %f\n", &nodefrom, &nodeto, &weight); //how many edges
        out("%d %d %f\n", nodefrom, nodeto, weight); 

        if(nodeto < cn) {
            //proceed normally
        }
        else {
            printf("ERROR: node %d outside of range (max %d)\n", nodeto,cn);
            continue; //skip this edge
        }

        edge e;
        e.from = nodefrom;
        e.to = nodeto;
        e.weight = weight;
        g[nodefrom].insert(std::make_pair(weight,e));

        e.to = nodefrom;
        e.from = nodeto;
        g[nodeto].insert(std::make_pair(weight,e));

        pq.insert(e);
    }
    out("size of g %d\n",g.size());


    printf("Case %d:\n", ++ord);
    print_graph(g);

    float totpath = MST(g, pq);
    printf ("Tot=%f\n", totpath);
    printf("\n");

  }

  return 0;
}

