/* Shortest paths for any directed graph even with negative edges 
 * this is what is referred to as the bllman-ford-rao algorithm
 * where we relax all edges E times, once for each vertex.
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
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 200000000

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(se::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d-%d(%.2f), ", it->from, it->to, it->weight);
        }
        out("\n");
    }
}


void printSP(std::vector<edge> P, int i, int final)
{
    std::vector<edge> s;
    while(i != final) {
        s.push_back(P[i]);
        i = P[i].from;
    }

    for(std::vector<edge>::const_reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit)
        printf("%d -> %d (%.2f) ",rit->from, rit->to, rit->weight);
}

//shortest path from a node n to every other node: 
//this is for any graphs even ones that have negative cycles
//for every vertex, relax E times
void ShortestPath(const graphtp & g, int n)
{
    int comparisons = 0;
    vi visited(g.size());
    vd D(g.size());
    std::vector<edge> P(g.size());

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        *it = INFINITY;
    D[n] = 0;

    //do the relaxation V times 
    for(int i = 0; i < g.size(); i++) {
        //for all vertices v get the distance from n
        for(int v = 0; v < g.size(); v++) {
            for(se::const_iterator it = g[v].begin(); it != g[v].end(); ++it)
            {
                float dist = D[v] + it->weight;
                assert(v == it->from && "not the same node");
                if(D[it->to] > dist) { //this is the relaxation step
                    D[it->to] = dist;
                    P[it->to] = *it;
                }
            }
        }
    }

    for(int i = 0; i < D.size(); i++) {
        printf("%d -> %d sp=%.2f ", n, i, D[i]);
        printSP(P, i, n);
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
