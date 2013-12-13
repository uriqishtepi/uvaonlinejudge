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


typedef struct {
    int from;
    int to;
    float weight;
} edge;


#define vi std::vector<int>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
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
            out("%d-%d(%.2f), ", it->second.from, it->second.to, it->second.weight);
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
//Dijkstra's this is for graphs that have no negative cycles
//start from node, and expand via BFS updating shortest path as you go
void ShortestPath(const graphtp & g, int n)
{
    int comparisons = 0;
    vi visited(g.size());
    vd D(g.size());
    std::vector<edge> P(g.size());

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        *it = INFINITY;
    D[n] = 0;

    //start with current in queue
    mdi q;
    edge e; e.from = n; e.to = n; e.weight = 0.0;
    q.insert(std::make_pair(0,n));
    out("initial n %d ", n);

    int counter = 0;
    while(!q.empty()) 
    {
        //pop first
        int node = q.begin()->second;
        q.erase(q.begin());

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
            float dist = D[node] + it->second.weight;
            out("dist from %d to %d; old dist %.2f vs new dist %.2f\n", 
                            node, it->second.to, D[it->second.to], dist);

            comparisons++;
            if(D[it->second.to] > dist) { //this is the relaxation step
                D[it->second.to] = dist;
                P[it->second.to] = it->second;
            }

            //if this were a priority queue, we would search for the to elements
            //and do decrease key on it -- so we would not insert again key
            //unfortunately we can not do so with a map
            q.insert(std::make_pair(D[it->second.to], it->second.to));
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
