/* this solves a 2 sat problem via the connected components algorithm
 * input is in the format 
 * 3 
 * 1 2
 * 2 -3
 * -1 3
 *
 * to mean there are three constraints, and they are
 * (x1 v x2) and (x2 v ~x3) and (~x1 v x3)
 *
 */
#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
void out(...) {}
#endif

#define vi std::vector<int>
#define graphtp std::vector< vi > 

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(size_t n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d, ", *it);
        }
        out("\n");
    }
}


void rec_topological_sort(const graphtp &g, vi & visited, vi & postorder, int node)
{
    visited[node] = gray;
    for(vi::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
    {
        if(visited[*it] == gray) {
            out("cycle detected node %d->%d\n", node, *it);
            continue;
        }        
        else if(visited[*it] == black) {
            out("encountered a prev. visited node %d\n", *it);
            continue;
        }
        rec_topological_sort(g, visited, postorder, *it);
    }
    visited[node] = black;
    postorder.push_back(node);
}


vi recursive_topological_sort(const graphtp &g)
{
    vi visited(g.size());
    vi postorder;
    for(size_t n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;
        rec_topological_sort(g, visited, postorder, n);
    } 

    out("postorder: ");
    for(size_t n = 0; n < postorder.size(); n++)
        out("%d ", postorder[n]);
    out("\n");

    out("reverse postorder: ");
    for(int n = postorder.size() - 1; n >= 0; n--)
        out("%d ", postorder[n]);
    out("\n");

    return postorder;
}


//compute the reverse graph
void get_reverse_graph(const graphtp &g, graphtp &rev)
{
    rev.resize(g.size());
    for(size_t n = 0; n < g.size(); n++)
    {
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it)
        {
            rev[*it].push_back(n);
        }
    }
}


//strongly conected comp vai the kosaraju sharir algorithms
//to run the topo sort on reverse graph, then run DFS taking nodes in that order
bool strongly_connected_components_kos_sharir(const graphtp &g, int m)
{
    graphtp rev;
    get_reverse_graph(g, rev);

    vi post = recursive_topological_sort(rev);
    vi visited(g.size());
    int counter = 0;
    //do DFS on g by taking order of post
    for(vi::const_reverse_iterator jt = post.rbegin(); jt != post.rend(); ++jt)
    {
        int n = *jt;
        if(visited[n]) //nothing more to do with this node
            continue;

        std::stack<int> k;
        k.push(n);
        counter++;

        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            k.pop();
            if(visited[node]) { //node can be put in stack mult times
                continue;
            }

            visited[node] = counter;

            out("%d ", node);

            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                out("considering %d -> %d \n", node, *it);
                if(visited[*it]) {
                    out("encountered a prev. visited node %d\n", *it);
                    continue;
                }
                k.push(*it);
            }
        }
    }

    out("\n");
    for(size_t n = 0; n < g.size(); n++)
        out("%2d ", n);
    out("\n");
    for(size_t n = 0; n < g.size(); n++)
        out(" ^ ");
    out("\n");
    for(size_t n = 0; n < g.size(); n++)
        out("%2d ", visited[n]-1);
    out("\n");
    int sat = true;
    for(size_t n = 0; n < m; n++)
    {
        if(visited[n] == visited[n + m]) {
            return false;
        }
    }
    return true;
}

//ads dependency in the direction (A v B) : -B -> A
inline void addDependency(graphtp & g, int m, int a, int b)
{   
    int from = (b < 0) ? (-b)   : b + m;
    //A v -B implies B -> A
    //A v B  implies -B -> A
    int to = (a < 0) ? (-a) + m : a;
    assert(from > 0 && from < g.size());
    assert(to > 0 && to < g.size());
    g[from].push_back(to);
}

int main(void)
{
  out("starting ...\n");
  int N = 0;
  int ord=0;
  scanf("%d", &N);
  out("m %d\n",N);
  while (ord++ < N) {
    int m; //nodes
    scanf("%d\n", &m);
    out("m %d\n",m);
    graphtp g(2*m+2);
    int counter = 0;
    int a, b;

    while(counter++ < m && scanf("%d %d", &a, &b) != EOF)
    {
        if(a > m || -a > m || b > m || -b > m) {
            printf("value %d or %d is not less than m %d\n", a, b, m);
            exit(1);
        }
        //(A v B) implies a dependency -B -> A and also -A -> B
        addDependency(g, m, a, b);
        addDependency(g, m, b, a);
    }

    print_graph(g);
    bool sat = strongly_connected_components_kos_sharir(g, m);
    printf("Case %d: ", ord);
    if(!sat)
        printf("Not satisfiable\n");
    else
        printf("Satisfiable\n");

  }
  return 0;
}
