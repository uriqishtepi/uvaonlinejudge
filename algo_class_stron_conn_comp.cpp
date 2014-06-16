#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <algorithm>
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

#define vi std::vector<int>
#define graphtp std::vector< vi > 

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(unsigned int n = 0; n < g.size(); n++)
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
    for(unsigned int n = 0; n < g.size(); n++)
    {
        if(white == visited[n])
            rec_topological_sort(g, visited, postorder, n);
    } 

    out("postorder: ");
    for(unsigned int n = 0; n < postorder.size(); n++)
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
    for(unsigned int n = 0; n < g.size(); n++)
    {
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it)
        {
            rev[*it].push_back(n);
        }
    }
}


void printGroups(vi & visited)
{
    std::sort(visited.begin(), visited.end());
    out("visited: ");
    for(vi::const_iterator cit = visited.begin(); cit!=visited.end();++cit){
        out("%d ",*cit);
    }
    out("\n");
    vi groups;

    vi::const_iterator pit = visited.begin();
    vi::const_iterator cit = pit+1; 
    int currcnt = 1;
    while(cit != visited.end()) {
        if(*cit == *pit) {
            currcnt++;
        }
        else {
            groups.push_back(currcnt);
            currcnt = 1;
            pit = cit;
        }
        cit++;
    }
    groups.push_back(currcnt);

    std::sort(groups.begin(), groups.end(), std::greater<int>());
    int i = 0;
    for(vi::const_iterator cit = groups.begin(); cit!=groups.end() && i < 10;++cit, i++){
        printf("%d ",*cit);
    }
    printf("\n");

}


//strongly conected comp vai the kosaraju sharir algorithms
//to run the topo sort on reverse graph, then run DFS taking nodes in that order
void strongly_connected_components_kos_sharir(const graphtp &g, const graphtp &rev)
{
    //graphtp rev;
    //get_reverse_graph(g, rev);

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
            out("visiting %d \n", node);

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

    for(unsigned int n = 0; n < g.size(); n++) {
        out("%d -> %d\n", n, visited[n]);
    }
    printGroups(visited);
}



int main(void)
{
  out("starting ...\n");
  std::cout << " DFS " << std::endl;

  int N; //test cases
  scanf("%d\n", &N);
  out("N %d\n",N);
  int ord = 0;
    
  while(N-- > 0) {
    char * buff = NULL;
    size_t n;
    int m; //nodes
    int counter = 0;
    scanf("%d\n", &m);
    out("m %d\n",m);
    graphtp g;
    g.resize(m);
    graphtp r;
    r.resize(m);

    while(getline(&buff, &n, stdin) != -1 )
    {
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        //out("this is node ='%s'\n", tok);
        if(tok == NULL) {
            continue;
        }
        int nodefrom = atoi(tok);
        //out("this is node ='%d'\n", nodefrom);

        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto < m) {
                out("red tok='%s'\n", tok);
                counter++;
                g[nodefrom].push_back(nodeto);
                r[nodeto].push_back(nodefrom);
            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }
            tok = strtok(NULL, " \n\t");
        }
    }
    printf("edge counter %d\n", counter);


    printf("Case %d:\n", ++ord);
    print_graph(g);

    strongly_connected_components_kos_sharir(g,r);
    printf("\n");

  }

  return 0;
}
