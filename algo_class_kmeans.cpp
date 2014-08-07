/* k-means clustering using kruskal mst algorithm
 * continue merging until there are onle k groups left
 */
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
    int weight;
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
#define mwp std::multimap<int, edge> //map weight and destination point 
#define graphtp std::vector< mwp >  //graph is a vector of maps -- the edges
#define pqtp std::multiset< edge, cmpedge >  //priority que

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(unsigned int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(mwp::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d(%d), ", it->second.to, it->second.weight);
        }
        out("\n");
    }
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
    int curr_a = a;
    int parent_a = uf[curr_a];

    while(uf[parent_a] != parent_a) //we found the root, its parent_a
    {
        uf[curr_a] = uf[parent_a]; //path compression to only the parent
        curr_a = parent_a; //load next parent
        parent_a = uf[parent_a];
    }

    int curr_b = b;
    int parent_b = uf[curr_b];

    while(uf[parent_b] != parent_b) //we found the root, its parent_b
    {
        uf[curr_b] = uf[parent_b]; //path compression to only the parent
        curr_b = parent_b; //load next parent
        parent_b = uf[parent_b];
    }

    if(parent_b == parent_a)
        return false;

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
int MST(const graphtp & g, pqtp & pq, int k)
{
    vi uf(g.size()); //union find structure
    int visited = 0;
    int totpath = 0.0;
    vi mindist;

    //for each vertex need a set
    for(int n = 0; n < g.size(); n++)
        uf[n] = n;

    pqtp::iterator it = pq.begin();
    while(it != pq.end() && visited < g.size()) {
        edge e = *it; //extract min
        pq.erase(it++);

        //out ("considering %d - %d (%d) \n", e.from, e.to, e.weight);
        //unionfind will return false if they are in the same tree
        if(false == unionfind(uf,e.to,e.from)) 
            continue;
        
        //process this edge
        totpath += e.weight;
        mindist.push_back(e.weight);
        printf ("%d - %d (%d) t=%d\n", e.from, e.to, e.weight, totpath);
        visited++;
    }
    out ("Tot=%d\n", totpath);
    out ("kclusterdist=%d\n", *(mindist.end()-k+1));
    return *(mindist.end()-k+1);
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
    scanf("%d\n", &cn); 
    out("cn %d\n", cn); 


    for(int i = 0; i < cn; ++i) {
        mwp me;
        g.push_back(me);
    }

    int nodefrom;
    int nodeto;
    int weight;
    int i = 0;
    while(scanf("%d %d %d\n", &nodefrom, &nodeto, &weight) != EOF )
    {
        i++;
        out("%d %d %d\n", nodefrom, nodeto, weight); 

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

        pq.insert(e);

        e.to = nodefrom;
        e.from = nodeto;
        g[nodeto].insert(std::make_pair(weight,e));

        pq.insert(e);
    }
    out("size of g %d\n",g.size());


    printf("Case %d:\n", ++ord);
    print_graph(g);

    int k = 4;
    int totpath = MST(g, pq, k);
    printf ("Tot=%d\n", totpath);
    printf("\n");

  }

  return 0;
}
