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



void DFS(const graphtp & g)
{
    vi visited(g.size());

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        std::stack<int> k;
        k.push(n);

        int counter = 0;
        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            if(visited[node] == black) {
                k.pop();
                continue;
            }

            if(visited[node] != gray) {
                printf("%d ", node);
            }
            out("%d: popped %d \n", counter++, node);
            visited[node] = gray;

            int anynew = 0;
            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(visited[*it] == gray) {
                    printf("cycle detected node %d->%d\n", node, *it);
                    continue;
                }        
                else if(visited[*it] == black) {
                    out("encountered a prev. visited node %d\n", *it);
                    continue;
                }
                k.push(*it);
                anynew++;
            }

            if(!anynew) {
                visited[node] = black;
                k.pop();
            }
        }
    }
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

    DFS(g);
    printf("\n");

  }

  return 0;
}
