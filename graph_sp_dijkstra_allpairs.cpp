/* this is an attempt to have all pairs shortest paths using the dijkstra 
 * algorigthm, by using a priority queue to insert all edges. 
 * Note that this does not currently find the shortest paths.
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
#define mwp std::multimap<double, edge> //map weight and destination point 
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
        if(a.from != b.from)
            return a.from < b.from;
        else if(a.to != b.to)
            return a.to < b.to;
        else
            return false;
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


void printMatrix(matrix & D, int size)
{
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
    matrix visited(g.size());
    forl(i, 0, g.size()) {
        forl(j, 0, g.size()) {
            visited(i,j) = 0;
        }
    }

    mwp q;

    forl(i, 0, g.size()) {
        edge e; e.from = i; e.to = i; e.weight = 0.0;
        q.insert(std::make_pair(0.0,e));
    }

    while( !q.empty() ) 
    {
        //pop first
        edge e = q.begin()->second;
        q.erase(q.begin());

        visited(e.from, e.to) = 1; 
        out("node %d->%d (%f)\n", e.from, e.to, e.weight);

        for(se::const_iterator it = g[e.to].begin(); it != g[e.to].end(); ++it) 
        {
            out("considering %d -> %d -> %d \n", e.from, e.to, it->to);
            if(visited(e.from,it->to) > 0)
                continue;

            assert(e.to == it->from);
            //compute new D(e.from, it->to)
            float dist = D(e.from,e.to) + it->weight;
            out("dist = %f \n", dist);
            if(D(e.from, it->to) > dist)
                D(e.from, it->to) = dist;

            edge ne; ne.from = e.from; ne.to = it->to; ne.weight = D(e.from, it->to);
            q.insert(std::make_pair(D(e.from, it->to), ne));
            visited(e.from,it->to) = 1;
        }

    }
    
    printMatrix(D, g.size());
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

    AllPairShortestPath(g);
    printf("\n");

  }

  return 0;
}
