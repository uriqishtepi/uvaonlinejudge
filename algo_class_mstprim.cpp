#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
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
    bool operator<(const edge &other) {
        return this->weight < other.weight;
    }
} ;


#define vi std::vector<int>
#define mwp std::multimap<int, edge> //map weight and destination point 
#define pq std::priority_queue<edge> //map weight and destination point 
#define graphtp std::vector< mwp >  //graph is a vector of maps -- the edges

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(mwp::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d(%d), ", it->second.to, it->first);
        }
        out("\n");
    }
}

//minimum spanning tree  -- Prims algorithm
//issues to solve: representation of the graph, edges connect two vertices
//and have a weight. when sorting the edges by weight, the same edge will 
//show up twice at a time so needs to be represented only once.
//it can run on a directed graph as well but it will not detect cycles
void MST(const graphtp & g)
{
    vi visited(g.size());
    mwp globl;
    int totpath = 0;

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;
        
        //start with current in queue
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
            int node = e.to;
            if(visited[node])
                continue;

            visited[node] = true;
            printf("%d - %d (%d)\n", e.from, node, e.weight);
            totpath += e.weight;

            out("\n%d: popped %d \n", counter++, node);

            for(mwp::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                out("considering %d -> %d \n", node, it->second.to);
                if(visited[it->second.to]) {
                    out("encountered a prev. visited node %d\n", it->second.to);
                    continue;
                }
                globl.insert(*it);
            }
        }
    }
    
    printf ("Tot=%d\n", totpath);
}



int main(void)
{
  out("starting ...\n");
  std::cout << " Prim's MST (min spanning tree) " << std::endl;

  int N; //test cases
  scanf("%d\n", &N);
  out("N %d\n",N);
  int ord = 0;
    
  while(N-- > 0) {
    char * buff = NULL;
    graphtp g;
    size_t n;
    int m; //nodes
    int es; //edges
    scanf("%d %d\n", &m, &es);
    out("m %d es %d\n",m,es);
    int counter = 0;
    g.resize(m);

    while(counter++ < es && getline(&buff, &n, stdin) != -1 )
    {
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        out("this is node ='%s'\n", tok);
        int nodefrom = atoi(tok);
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto < m) {
                out("red tok='%s'\n", tok);
            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }

            tok = strtok(NULL, " \n\t");
            if(tok == NULL)
                printf("ERROR: weight must be given for each link \n");

            int weight = atof(tok);
            edge e;
            e.from = nodefrom;
            e.to = nodeto;
            e.weight = weight;

            g[nodefrom].insert(std::make_pair(weight,e));

            edge f;
            f.from = nodeto;
            f.to = nodefrom;
            f.weight = weight;
            g[nodeto].insert(std::make_pair(weight,f));

            tok = strtok(NULL, " \n\t");
        }
        out("size of g %d\n",g.size());
    }


    printf("Case %d:\n", ++ord);
    print_graph(g);

    MST(g);
    printf("\n");

  }

  return 0;
}
