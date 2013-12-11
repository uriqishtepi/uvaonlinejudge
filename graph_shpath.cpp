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

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


typedef struct {
    int from;
    int to;
    float weight;
} edge;


#define vi std::vector<int>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define graphtp std::vector< mwp >  //graph is a vector of maps -- the edges
#define INFINITY 200000000

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(mwp::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d-%d(%f), ", it->second.from, it->second.to, it->second.weight);
        }
        out("\n");
    }
}

//shortest path from a node n to every other node: 
//start from node, and expand via BFS updating shortest path as you go
//for directed acyclic graphs
void ShortestPath(const graphtp & g, int n)
{
    vi visited(g.size());
    vd D(g.size());

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        *it = INFINITY;
    D[n] = 0;

    //start with current in queue
    std::queue<int> q;
    q.push(n);

    visited[n] = true;
    out("initial n %d ", n);

    int counter = 0;
    while(!q.empty()) 
    {
        //pop first
        int node = q.front();
        q.pop();

        visited[node] = true;
        out("n - %d\n", node);

        out("\n%d: popped %d \n", counter++, node);

        for(mwp::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
        {
            assert(it->second.from == node && "encountered an inconsistend element");
            out("considering %d -> %d \n", node, it->second.to);
            if(visited[it->second.to]) {
                out("encountered a prev. visited node %d\n", it->second.to);
                continue;
            }
            q.push(it->second.to);
            float dist = D[node] + it->second.weight;
            out("dist from %d to %d; old dist %f vs new dist %f\n", node, it->second.to, D[it->second.to], dist);
            if(D[it->second.to] > dist)
                D[it->second.to] = dist;
        }
    }

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        printf("%f ", *it);
    printf("\n");
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

        mwp me;
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
            me.insert(std::make_pair(weight,e));

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
