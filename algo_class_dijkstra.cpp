/* shortest path from a node n to every other node, known as
 * Dijkstra's algorithm. This is for graphs that have no negative cycles
 * start from the origin node, and expand via BFS updating shortest path as you go
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




#define vi std::vector<int>
#define vd std::vector<int>
#define mwp std::map<int, edge> //map weight and destination point 
#define mdi std::multimap<int, int>  //map int int
#define se std::multiset<edge, cmpedge>  //set of edges
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges
#define INFINITY 1000000

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


//shortest path from a node n to every other node: 
//Dijkstra's this is for graphs that have no negative cycles
//start from node, and expand via BFS updating shortest path as you go
void ShortestPath(const graphtp & g, int n)
{
    int comparisons = 0;
    vi visited(g.size());
    vd D(g.size());
    std::vector<edge> P(g.size());
    
    //start with current in queue
    mdi q; //poor man's queue: map of weight to from_node
    mdi rev; //node and lowest weight to it


    int i = 0;
    for(vd::iterator it = D.begin(); it != D.end(); ++it) {
        if(i != n) {
            *it = INFINITY;
            q.insert(std::make_pair(INFINITY,i));
        }
        i++;
    }
    D[n] = 0;
    q.insert(std::make_pair(0,n));

    out("initial n %d\n", n);

    int counter = 0;
    while(!q.empty()) 
    {
        //pop first
        int node = q.begin()->second;
        q.erase(q.begin());

        visited[node] = true;
        out("n - %d\n", node);

        out("\n%d: popped %d \n", counter++, node);

        for(se::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
        {
            if(it->from != node) 
                printf("%d != %d\n", it->from, node);
            assert(it->from == node && "encountered an inconsistend element");
            out("considering %d -> %d \n", node, it->to);

            if(visited[it->to]) { //need to check because q allows dup nodes
                out("encountered a prev. visited node %d\n", it->to);
                continue;
            }

            int dist = D[node] + it->weight;
            out("dist from %d to %d; old dist %d vs new dist %d\n", 
                            node, it->to, D[it->to], dist);

            comparisons++;
            if((comparisons % 100000) == 1)
                out("comparisons %d D.size()=%d q.size()=%d\n", comparisons, D.size(), q.size());
            if(D[it->to] > dist) { //this is the relaxation step
                int old = D[it->to];
                D[it->to] = dist;
                P[it->to] = *it;

                //already in q so need to delete it first and add it
                mdi::iterator qit = q.find(old);
                if(qit == q.end() ) printf("relax qit is end() for %d\n", old);
                assert(qit != q.end() && "not found in q");
                while(qit->second != it->to) qit++; //find the actual node
                q.erase(qit);

                q.insert(std::make_pair(D[it->to], it->to));
            }

            //if this were a priority queue, we would search for the to elements
            //and do decrease key on it -- so we would not insert again key
            //unfortunately we can not do so with a map
        }
    }

    for(int i = 0; i < D.size(); i++) {
        printf("%d -> %d sp=%d ", n, i, D[i]);
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
        char * tok = strtok(buff, " \n\t"); //node from
        out("this is node ='%s'\n", tok);
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }
        int nodefrom = atoi(tok);

        se me;
        tok = strtok(NULL, " \n\t"); //node 
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto < m) {
                out("red (node) tok='%s'\n", tok);
            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }

            tok = strtok(NULL, " \n\t"); //weight
            if(tok == NULL)
                printf("ERROR: weight must be given for each link \n");

            int weight = atoi(tok);
            out("red (weight) tok='%s'\n", tok);

            edge e;
            e.from = nodefrom;
            e.to = nodeto;
            e.weight = weight;
            out("inserting e %d %d %d\n",e.from, e.to, e.weight);
            me.insert(e);

            tok = strtok(NULL, " \n\t"); //node
        }
        g.push_back(me);
        out("size of g %d\n",g.size());
    }

    printf("Case %d:\n", ++ord);

    if(g.size() != m) {
        printf("need to have all the nodes explicitly defined, even if no links\n");
        continue;
    }


    print_graph(g);

    ShortestPath(g, 0);
    printf("\n");

  }

  return 0;
}
