#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define vi std::vector<int>
#define graphtp std::vector< vi > 

enum {white=0, gray=1, black=2,};

struct edge {
    int from;
    int to;
};

#define ve std::vector<edge>

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



//need genuine copy of the parameters
int mincut(int nodes, ve alledges)
{
    while(nodes > 2) {
        //pick edge randomly 
        ve nall;
        int i = rand() % alledges.size();
        edge eg = alledges[i];
        out("merging eg(%d,%d), nodes = %d\n", eg.from, eg.to, nodes);

        //merge node with neigbor, any .to turn it into .from
        for(ve::iterator it = alledges.begin(); it != alledges.end(); ) {
            //remove self loops
            if((it->from == eg.to && it->to == eg.from) 
              || (it->from == eg.from && it->to == eg.to)) {
                it = alledges.erase(it); //returns the it following the erased
            }
            else if(it->from == eg.to) {
                it->from = eg.from;
                it++;
            }
            else if(it->to == eg.to) {
                it->to = eg.from;
                it++;
            }
            else it++;
        }
        nodes--;
    }

    //whatever is left is the cut
    return alledges.size();
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
    ve alledges;
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
        int from = atoi(tok);

        vi e;
        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto <= m && from != nodeto) {
                out("red tok='%s'\n", tok);
                e.push_back(nodeto);

                edge eg;
                eg.from = from;
                eg.to = nodeto;
                alledges.push_back(eg); 

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

    static timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);

    int allmin = 100000;
    int  mn;
    for(int i = 0; i < g.size()*g.size() ; i++) { //run n*n times
        mn = mincut(g.size(), alledges);
        printf("%d) min = %d allmin = %d\n", i, mn, allmin);
        if(allmin > mn) 
            allmin = mn;
    }
    printf("Tot mn = %d\n", allmin);

  }

  return 0;
}
