/* Produces all possible paths in a graph, and find Hamiltonian path if exists
 *
 * One way to do this is by producing all permutations, 
 * then if a permutation is a valid path, it prints it.
 *
 * However the above is too slow, a better way is the following:
 * Start at each node and perform a dfs marking this node as visited 
 * and cleaning up after the dfs search. 
 *
 * If the path found has length of size graph size - 1, then we have found
 * a Hamilton path.  See also graph_dfs.cpp on a way of implementing this.
 * Hamilton path is NP-complete problem: find a path that goes through every 
 * vertex exactly once
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
#define ve std::vector<edge>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
#define se std::set<edge, cmpedge>  //set of edges
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 200000000



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
    inline double & operator()(int a, int b) { return m_vec[a*m_sz + b]; }
    int m_sz;
    std::vector<double>m_vec;
};



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

void printPath(std::vector<edge> P, int maxsz)
{
    for(std::vector<edge>::const_iterator it = P.begin(); it != P.end(); ++it)
        printf("%d -> %d (%.2f) ",it->from, it->to, it->weight);
    if(P.size() == maxsz - 1)
        printf(" *"); //identifies a hamiltonian path
    printf("\n");
}


void dfs(int node, vi &v, ve &P, const graphtp & g) 
{
    v[node] = 1; //mark 
    for(se::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
    { 
        assert(it->from == node);
        int next = it->to;
        if(v[next]) continue;

        P.push_back(*it);
        printPath(P, g.size()); //print this path

        dfs(next, v, P, g);
        P.erase(P.end()-1);
    }
    v[node] = 0; //cleanup 
}

void AllPaths(const graphtp & g)
{
    int comparisons = 0;
    vi v(g.size());
    ve P;

    forl(i, 0, g.size()) { //for each vertex i
        dfs(i, v, P, g);
    }
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

    AllPaths(g);
    printf("\n");

  }

  return 0;
}
