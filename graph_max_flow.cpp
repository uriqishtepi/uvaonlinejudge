/* Ford fulkerson to find max flow, min cut
 * its a grid algorithm although it can be solved via simplex algorithm */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <queue>
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
    float capacity;
    float flow;
    int from;
    int to;
    bool backedge;

    bool operator<(const edge & other) {
        out("****** operrator < \n");
        return this->capacity < other.capacity;
    }
};

struct cmpedge {
    bool operator()(const edge & a, const edge &b) {
        out("$$$$$$ operrator () \n");
        return a.capacity < b.capacity;
    }
};




#define vi std::vector<int>
#define vd std::vector<double>
#define ve std::vector<edge>
#define vpe std::vector<edge *>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
#define se std::set<edge, cmpedge>  //set of edges
#define si std::set<int>
#define graphtp std::vector< ve >  //graph is a vector of maps -- the edges
#define INFINITY 200000000

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(ve::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d-%d(%.2f/%.2f), ", it->from, it->to, it->flow, it->capacity);
        }
        out("\n");
    }
}


float getResidual(edge & e, int from, int to)
{
    assert(e.from == from && "from does not match");
    assert(e.to == to && "from does not match");

    if(e.backedge) return e.flow;
    else return e.capacity - e.flow;
}

//this is a shortest path algorithm to find an aumenting path
//if an edge can carry more flow, or if a backedge can diminish more flow
//that is the residual capacity, and that node gets marked and put in the que.
//
//to find the nodes in the mincut side, we look at the marked nodes, 
//ie the nodes that are reachable from source are in one side, and mincut
//is the connections to the other side of the graph.
bool hasAugmentingPath(graphtp & g, int src, int dest, vpe & P)
{
    out("hasAugmentingPath: entering\n");
    P.clear();
    P.reserve(g.size());

    vi marked(g.size());
    std::queue<int> q;

    q.push(src);
    marked[src] = true;

    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        out("q.top=%d\n", node);

        for(ve::iterator it = g[node].begin(); it != g[node].end(); ++it)
        {
            out("edge %d-%d(%.2f/%.2f) \n", it->from, it->to, it->flow, it->capacity);

            assert(node == it->from && "Edge does not have same from as node");
            int w = it->to;
            float resid_capac_to_w = getResidual(*it, it->from, it->to);

            out("resid cap %d -> %d = %f (%f - %f)\n", node, w, resid_capac_to_w, it->capacity, it->flow);
            if(resid_capac_to_w > 0 && !marked[w]) {
                P[w] = const_cast<edge *> (&(*it));
                out("setting P[%d] to = %ld\n",w, P[w]);
                assert(P[w] != NULL && "address of edge is null");
                marked[w] = true;
                q.push(w);
            }
        }
    }

    out("hasAugmentingPath: returning %d\n\n", marked[dest]);
    return marked[dest];
}


/* Maxflow / mincut algorithm :
 * while has augmenting path
 *   find augmenting path
 *   calculate new capacities
 */
void MaxFlow(graphtp & g, int src, int dest)
{
    out("Maxflow: entering\n");
    float flowvalue = 0;
    vpe P(g.size()); //parent node for node e.to is e.from

    while(hasAugmentingPath(g, src, dest, P)) 
    {

        float capacity = INFINITY;
        //find capacity
        for(int v = dest; v != src; v = P[v]->from) {
            out("v=%d\n", v);
            assert(P[v] != NULL && "address of edge is null");
            float resid_capac = getResidual(*P[v], P[v]->from, v);
            capacity = std::min(capacity, resid_capac);
            assert(capacity > 0 && "Capacity is negative ");
            out("reading P[%d] (0x %ld), from=%d,to=%d,flow/cap=%f/%f residcap %f, capacity=%f\n",v, P[v], P[v]->from, P[v]->to, P[v]->flow, P[v]->capacity, resid_capac, capacity);
        }
        
        //augment flow by capacity
        for(int v = dest; v != src; v = P[v]->from) {
            float cap = capacity;
            if(P[v]->backedge) 
                cap = -cap;

            out("augment P[%d]->flow = %f by %f\n",v, P[v]->flow, cap);
            P[v]->flow += cap;
        }

        flowvalue += capacity;
        out("flowvalue = %f\n\n", flowvalue);
    }
    printf("Maxflow = %f\n", flowvalue);
}



int main(void)
{
  out("starting ...\n");
  std::cout << " MaxFlow " << std::endl;

  int N; //test cases
  scanf("%d\n", &N);
  out("N %d\n",N);
  int ord = 0;
    
  while(N-- > 0) {
    char * buff = NULL;
    graphtp g;
    size_t n;
    int m; //nodes
    scanf("%d\n", &m);
    out("m %d\n",m);
    int counter = 0;

    for(int i = 0; i < m; i++) {
        g.push_back(ve());
    }
    out("size of g %d\n",g.size());


    while(counter++ < m && getline(&buff, &n, stdin) != -1 )
    {
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        out("this is node ='%s'\n", tok);
        int nodefrom = atoi(tok);
        assert(nodefrom < m && "nodefrom is more than m");

        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto < m) {
                out("red (node) tok='%s'\n", tok);
            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }

            tok = strtok(NULL, " \n\t");
            if(tok == NULL)
                printf("ERROR: capacity must be given for each link \n");

            float capacity = atof(tok);
            out("read (capacity) tok='%s'\n", tok);

            edge e;
            e.from = nodefrom;
            e.to = nodeto;
            e.flow = 0;
            e.capacity = capacity;
            e.backedge = false;
            g[nodefrom].push_back(e);
            out("inserting  %d -> %d\n", nodefrom, nodeto);

            e.to = nodefrom;
            e.from = nodeto;
            e.backedge = true;
            g[nodeto].push_back(e);
            out("inserting  %d -> %d\n", nodeto, nodefrom);

            tok = strtok(NULL, " \n\t");
        }
        out("size of g %d\n",g.size());
    }


    printf("Case %d:\n", ++ord);
    print_graph(g);

    MaxFlow(g, 0, g.size() - 1);
    printf("\n");

  }

  return 0;
}
