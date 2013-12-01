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


//breadth first search
//expand the reach from a node, level at at time
//extremely hard to find cycles with bfs
void BFS(const graphtp & g)
{
    vi visited(g.size());

    //consider all
    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        //start with current in queue
        std::queue<int> q;
        q.push(n);
        visited[n] = true;

        int counter = 0;
        while(!q.empty())
        {
            int el = q.front();
            q.pop();

            printf("%d ", el);

            for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
            {
                if(visited[*it]) 
                    continue;

                q.push(*it);
                visited[*it] = true;
            }
        }
        printf("\n");
    }
}


int main(void)
{
  out("starting ...\n");
  std::cout << " BFS " << std::endl;

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

    BFS(g);
  }

  return 0;
}
