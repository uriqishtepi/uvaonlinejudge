/* small program to convert from format of the class 
 *  1 2 0.3
 *  1 3 0.5
 * to the one i use in my programs
 *  1 2 0.3 3 0.5
 *
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


#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
#define se std::set<edge, cmpedge>  //set of edges
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 200000000



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


struct matrix {
    matrix(int s) : m_sz(s), m_vec(s*s) 
    {
        forl(i, 0, m_vec.size()) {
            m_vec[i] = INFINITY;
        }
        forl(i, 0, m_sz) {
            operator()(i,i) = 0.0;
        }
    }
    inline int & operator()(int a, int b) { return m_vec[a*m_sz + b]; }
    int m_sz;
    std::vector<int>m_vec;
};



enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    printf("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        printf("%d ", n);
        for(se::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            assert (it->from == n);
            printf("%d %d  ", it->to, it->weight);
        }
        printf("\n");
    }
}

int main(void)
{
  out("starting ...\n");
  std::cout << " Converting " << std::endl;

  int N = 1; //test cases
  //scanf("%d\n", &N);
  //out("N %d\n",N);
  int ord = 0;
    
  while(N-- > 0) {
    graphtp g;
    int cn; //count nodes
    int edgecount; 
    scanf("%d %d\n", &cn, &edgecount);
    out("m %d\n",cn);

    for(int i = 0; i < cn; ++i) {
        se me;
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
        g[nodefrom].insert(e);
    }
    out("size of g %d\n",g.size());

    out("i %d edgecount %d\n",i, edgecount);
    assert(i == edgecount);

    printf("Case %d:\n", ++ord);
    print_graph(g);
    printf("\n");

  }

  return 0;
}
