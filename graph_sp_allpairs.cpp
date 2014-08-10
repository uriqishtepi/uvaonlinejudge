/* 
 * This is the all pairs shortest paths algorithm known as Floyd Warshall Roy 
 * algorithm: it works by relaxing V times each pair of vertices (V^2 of them) 
 * thus it is a V^3 algorithm, with V^2 space for the Distances among each pair
 *
 * If there are any negative cycles, this algorithm can detect them by looking
 * at the diagonal of the Distances, if any value is < 0 then there is a cycle.
 *
 * To reconstruct the shortest paths would need extra VxV lists, one for each path.
 */
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
#define INFINITY INT_MAX



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


//this abstracts a square matrix structure 
//constructor initializes with zero in diagonal and INF elsewhere
struct matrix {
    matrix(size_t s) : m_sz(s), m_vec(s*s) 
    {
        forl(i, 0, m_vec.size()) {
            m_vec[i] = INFINITY;
        }
        forl(i, 0, m_sz) {
            operator()(i,i) = 0.0;
        }
    }
    size_t getCardinality() {return m_sz;}
    inline double & operator()(int a, int b) { return m_vec[a*m_sz + b]; }
    size_t m_sz;
    std::vector<double>m_vec;
};



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


void printSP(matrix & D, matrix & P, int src, int dest)
{
    if(src == dest)
        return;
    else if(P(src,dest) == INFINITY) //TODO:??
        printf("%d -> %d (%.2f) ",src, dest, D(src,dest));
    else {
        int k = P(src, dest);
        if(k != src) printSP(D, P, src, k);
        if(k != dest) printSP(D, P, k, dest);
    }
}



void printAllSP(matrix & D, matrix & P)
{
    size_t size = D.getCardinality();
    forl(i, 0, size) { 
        if(D(i,i) < 0) {
            printf("negative cycles exists distance %d to %d is %f\n", i, i, D(i,i));
            return;
        }
    }

    forl(i, 0, size) { 
        forl(j, 0, size) { 
            if(INFINITY == D(i,j))
                printf("%d -> %d sp=INF ");
            else {
                printf("%d -> %d sp=%.2f ", i,j, D(i,j));
                printSP(D, P, i, j);
            }
            printf("\n");
        }
    }
}


void printMatrix(matrix & D)
{
    size_t size = D.getCardinality();
    forl(i, 0, size) { 
        if(D(i,i) < 0) {
            printf("negative cycles exists distance %d to %d is %f\n", i, i, D(i,i));
            return;
        }
    }

    forl(i, 0, size) { 
        forl(j, 0, size) { 
            if(INFINITY == D(i,j))
                printf("%d -> %d sp=INF ", i,j);
            else
                printf("%d -> %d sp=%.2f ", i,j, D(i,j));
            printf("\n");
        }
    }
}



void AllPairShortestPath(const graphtp & g)
{
    int comparisons = 0;
    matrix D(g.size()); //initialized to infinity except for the diagonal
    matrix P(g.size()); //initialized to infinity except for the diagonal

    //populate D with all the edges in the graph
    forl(i, 0, g.size()) { //for all vertices v set D entry for edges out of v
        for(se::const_iterator it = g[i].begin(); it != g[i].end(); ++it)
        D(i, it->to) = it->weight;
    }

    forl(k, 0, g.size()) { //for each intermediate vertex k 
        forl(i, 0, g.size()) { //relax the distance between i and j
            forl(j, 0, g.size()) { 
                double & a = D(i,k);
                if(a == INFINITY) 
                    continue;
                double & b = D(k,j);
                if(b == INFINITY)
                    continue;

                double curr = a + b;
                double & d = D(i,j);
                if(d > curr) { //the so called relaxation step
                    d = curr;
                    P(i,j) = k; //the path from i to j uses edge k
                }
            }
        }
    }
    
    //printMatrix(D);
    printAllSP(D, P);
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
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        out("this is node ='%s'\n", tok);
        int nodefrom = atoi(tok);
        assert(nodefrom == counter-1);

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

    AllPairShortestPath(g);
    printf("\n");

  }

  return 0;
}
