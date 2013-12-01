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
#define out
#endif

#define vi std::vector<int>
#define graphtp std::vector< vi > 

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d, ", *it);
        }
        out("\n");
    }
}


//recursive DFS which can be also used on directed graphs
void DFS_visit(const graphtp & g, vi & visited, int n, int comp)
{
    out("DFS_visit n %d\n", n);
    visited[n] = comp;
    out("%d ", n);
    for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if(visited[*it]) continue;
        DFS_visit(g, visited, *it, comp);
    }
}


void connected_components(const graphtp & g)
{
    out("Connected Components g.size %d\n", g.size());
    vi visited(g.size());
    assert(visited.size() == g.size() && "Vector not same size");

    int comp = 0;
    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n]) continue;
        DFS_visit(g, visited, n, ++comp);
    }
    for(int n = 0; n < g.size(); n++)
        printf("%d ", n);
    printf("\n");
    for(int n = 0; n < g.size(); n++)
        printf("^ ");
    printf("\n");
    for(int n = 0; n < g.size(); n++)
        printf("%d ", visited[n]-1);
    printf("\n");

}




int main(void)
{
  out("starting ...\n");
  std::cout << " Connected Components " << std::endl;

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
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        vi e;
        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto < m) {
                out("red tok='%s'\n", tok);
                e.push_back(nodeto);
            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }
            tok = strtok(NULL, " \n\t");
        }
        g.push_back(e);
        out("size of g %d\n",g.size());
    }


    printf("Case %d:\n", ++ord);
    print_graph(g);

    connected_components(g);
  }

  return 0;
}
