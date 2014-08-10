/* this is the all pairs shortest paths algorithm known as Floyd Warshall Roy 
 * algorithm: it works by relaxing V times each pair of edges (V^2 of them) 
 * thus it is a V^3 algorithm, with V^2 space for the Distances among each pair
 * If there are any negative cycles, this algorithm can detect them; looking
 * at the diagonal of the Distances, if any value is < 0 then there is a cycle.
 * To reconstruct the shortest paths would need extra VxV lists, one for each path.
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


void printSP(std::vector<edge> P, int i, int final)
{
    std::vector<edge> s;
    while(i != final) {
        s.push_back(P[i]);
        i = P[i].from;
    }

    for(std::vector<edge>::const_reverse_iterator rit = s.rbegin(); rit != s.rend(); ++rit)
        printf("%d -> %d (%d) ",rit->from, rit->to, rit->weight);
}


void printMatrix(matrix & D, int size)
{
    forl(i, 0, size) { 
        if(D(i,i) < 0) {
            printf("negative cycles exists distance %d to %d is %d\n", i, i, D(i,i));
            return;
        }
    }

    forl(i, 0, size) { 
        forl(j, 0, size) { 
            if(INFINITY == D(i,j))
                printf("%d -> %d sp=INF ", i,j);
            else
                printf("%d -> %d sp=%d ", i,j, D(i,j));
            printf("\n");
        }
    }
}



void AllPairShortestPath(const graphtp & g)
{
    matrix D(g.size()); //initialized to infinity except for the diagonal

    forl(i, 0, g.size()) { //for all vertices v get the distance from n
        for(se::const_iterator it = g[i].begin(); it != g[i].end(); ++it)
        D(i, it->to) = it->weight;
    }

    forl(k, 0, g.size()) { //for each intermediate vertix k 
        forl(i, 0, g.size()) { //relax the distance between i and j
            forl(j, 0, g.size()) 
            { 
                int a = D(i,k); 
                if(a == INFINITY)
                    continue;

                int b = D(k,j); 
                if(b == INFINITY)
                    continue;

                int curr = a + b;
                int & d = D(i,j);

                if(d > curr) //the so called relaxation step
                    d = curr;
            }
        }
    }
    
    printMatrix(D, g.size());
}



int main(void)
{
  out("starting ...\n");
  std::cout << " ShortestPath " << std::endl;

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
    //print_graph(g);

    AllPairShortestPath(g);
    printf("\n");

  }

  return 0;
}
