/* Shortest paths for any directed graph even with negative edges 
 * this is what is referred to as the Bellman-Ford-Moore algorithm
 * where we relax all edges V times, once for each vertex.
 * This is a V^2 algorithm, with V amount of space for the Distances
 * of each vertex from the starting vertex.
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
    float weight;
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




#define vi std::vector<int>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
#define se std::set<edge, cmpedge>  //set of edges
#define si std::set<int>
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 200000000

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(size_t n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(se::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d-%d(%.2f), ", it->from, it->to, it->weight);
        }
        out("\n");
    }
}


//print shortest path from source vertex source to vertex i
//the data is stored in predecesor order in p
//so we need to traverse from i till the source vertex, and print in reverse
void printSP(std::vector<edge> P, int node, int src)
{
    std::vector<edge> s;
    while(node != src && s.size() <= P.size()) {
        s.push_back(P[node]);
        node = P[node].from;
    }

    for(std::vector<edge>::const_reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit)
        printf("%d -> %d (%.2f) ",rit->from, rit->to, rit->weight);
}


//shortest path from a node n to every other node: 
//this is for any graphs even ones that have negative weights -- can detect negative cycles
//for every vertex, relax E times
//as an optimization we use a queue to store vertices that changed
//and relax paths only from that queue
//to detect negative loops can check if node n gets updated on any the n-th iteration
void ShortestPath(const graphtp & g, int src)
{
    int comparisons = 0;
    vi visited(g.size());
    vd D(g.size());     //distances from source node to every other node
    std::vector<edge> P(g.size()); //parent node for node e.to is e.from

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        *it = INFINITY;
    D[src] = 0;

    si lastupdated;

    //keep a queue (set) of vertices (nodes) that were updated last time around
    //do the relaxation V times 
    for(size_t i = 0; i < g.size(); i++) {
        lastupdated.insert(i);
    }


    //without optimization loop would be: for(int i = 0; i < g.size(); i++) 
    size_t counter = 0;
    while(!lastupdated.empty()) {
        counter++;
        si newlast;
        //visit and relax all edges (two for loopxs needed to visit all edges)
        for(si::iterator jt = lastupdated.begin();jt != lastupdated.end(); jt++)
        {
            int v = *jt;
            out("next to work on is %d\n", v);
            for(se::const_iterator it = g[v].begin(); it != g[v].end(); ++it)
            {
                float dist = D[v] + it->weight;
                assert(v == it->from && "not the same node");
                if(D[it->to] > dist) { //this is the relaxation step
                    out("counter %d, it->to %d\n", counter, it->to);
                    if(counter >= g.size()) { 
                        //we should not update a node in a stage greater than sz
                        printf("negative cycles exists distance %d to %d is %f\n", v, it->to, dist);
                        //need to trace back from P[v]
                        //printSP(P, it->to, v);
                        printSP(P, v, it->to);
                        printf("\n");
                        return;
                    }
                    D[it->to] = dist;
                    P[it->to] = *it;
                    newlast.insert(it->to); //track which changed
                    out("new distance %d to %d is %f\n", v, it->to, dist);
                }
            }
        }
        lastupdated = newlast;
    }

    for(int i = 0; i < D.size(); i++) {
        printf("%d -> %d sp=%.2f ", src, i, D[i]);
        printSP(P, i, src);
        printf("\n");
    }
    out("comparisons %d\n", comparisons);
}



int main(void)
{
  out("starting ...\n");
  std::cout << " ShortestPath " << std::endl;

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

    while(counter++ < m && getline(&buff, &n, stdin) != -1 )
    {
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        out("this is node ='%s'\n", tok);
        int nodefrom = atoi(tok);
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        se me;
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
                printf("ERROR: weight must be given for each link \n");

            float weight = atof(tok);
            out("red (weight) tok='%s'\n", tok);

            edge e;
            e.from = nodefrom;
            e.to = nodeto;
            e.weight = weight;
            me.insert(e);

            tok = strtok(NULL, " \n\t");
        }
        g.push_back(me);
        out("size of g %d\n",g.size());
    }


    printf("Case %d:\n", ++ord);
    print_graph(g);

    ShortestPath(g, 0);
    printf("\n");

  }

  return 0;
}
