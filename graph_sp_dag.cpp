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
#define ve std::vector<edge>
#define mwp std::map<double, edge> //map weight and destination point 
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



//recursive topological sort, does a DFS and puts the nodes in the postorder
//vector with the furthest one going in first (ie is last in topological order)
//returnsthe nodes in postorder, topological order is the reverse of postorder
//so you would traverse from the end of the array postorder
void rec_topological_sort(const graphtp &g, vi & visited, vi & postorder, int node)
{
    visited[node] = gray;

    for(se::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
    {
        assert(it->from == node && "encountered an inconsistend element");
        out("considering %d -> %d \n", node, it->to);
        if(visited[it->to] == gray) {
            printf("cycle detected node %d->%d\n", node, *it);
            continue;
        }
        else if(visited[it->to] == black) {
            out("encountered a prev. visited node %d\n", it->to);
            continue;
        }

        rec_topological_sort(g, visited, postorder, it->to);
    }
    visited[node] = black;
    postorder.push_back(node);
}




//shortest path from a node n to every other node: 
//for edge weighted DAGs which means that there is no cycles
//start from node, and expand by considering nodes in topological order
//topological order ensures that you will not need to ever reconsider a node
//after you have computed the distance from the source, because there is no
//other way to get to that node
void ShortestPath(const graphtp & g, int n)
{
    int comparisons = 0;
    vi visited(g.size());
    vd D(g.size());
    ve P(g.size());

    for(vd::iterator it = D.begin(); it != D.end(); ++it) 
        *it = INFINITY;
    D[n] = 0;


    out("initial n %d ", n);
    vi postorder;
    rec_topological_sort(g, visited, postorder, n); //returns in postorder
    
    //consider the vertices in topological order(reverse postorder: use rbegin)
    for(vi::const_reverse_iterator cit = postorder.rbegin(); cit!= postorder.rend();++cit)
    {
        int node = *cit;
        for(se::const_iterator cjt = g[node].begin(); cjt!= g[node].end();++cjt)
        {
            assert(node == cjt->from && "from needs to be same as node");
            float dist = D[node] + cjt->weight;
            out("dist from %d to %d; old dist %.2f vs new dist %.2f\n", 
                    cjt->from, cjt->to, D[cjt->to], dist);

            comparisons++;
            //to get longest path (only DAGs), we would reverse this comparison
            if(D[cjt->to] > dist) { //this is the relaxation step
                D[cjt->to] = dist;
                P[cjt->to] = *cjt;
            }
            else
                out("attempted to update node...from %f to %f\n",D[cjt->to],dist );
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
