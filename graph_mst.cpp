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

#define vi std::vector<int>
#define mwp std::map<float, int> //map weight and destination point 
#define graphtp std::vector< mwp >  //graph is a vector of maps -- the edges

enum {white=0, gray=1, black=2,};

typedef struct {
    int from;
    int to;
    float weight;
} edge;


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(mwp::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d(%f), ", it->second, it->first);
        }
        out("\n");
    }
}

//minimum spanning tree 
//issues to solve: representation of the graph, edges connect two vertices
//and have a weight. when sorting the edges by weight, the same edge will 
//show up twice at a time so needs to be represented only once.
//it can run on a directed graph as well but it will not detect cycles
void MST(const graphtp & g)
{
    vi visited(g.size());
    mwp globl;

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;
        
        //start with current in queue
        std::queue<int> q;
        globl.insert(g[n].begin(),g[n].end());
        out("length of globl %d\n", globl.size());

        visited[n] = true;
        printf("n %d ", n);

        int counter = 0;
        while(!globl.empty()) 
        {
            //pop first
            std::pair<float,int> e = *globl.begin();
            globl.erase(globl.begin());
            if(visited[e.second])
                continue;

            visited[e.second] = true;
            printf("%d (%f) ", e.second, e.first);

            out("\n%d: popped %d \n", counter++, e.second);

            for(mwp::const_reverse_iterator it = g[e.second].rbegin(); it != g[e.second].rend(); ++it)
            {
                out("considering %d -> %d \n", e.second, it->second);
                if(visited[it->second]) {
                    out("encountered a prev. visited node %d\n", it->second);
                    continue;
                }
                globl.insert(*it);
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

        mwp e;
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

            float weight = atof(tok);
            e.insert(std::make_pair(weight,nodeto));

            tok = strtok(NULL, " \n\t");
        }
        g.push_back(e);
        out("size of g %d\n",g.size());
    }


    printf("Case %d:\n", ++ord);
    print_graph(g);

    MST(g);
    printf("\n");

  }

  return 0;
}
