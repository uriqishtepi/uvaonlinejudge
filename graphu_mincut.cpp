/* ccmpute the min cut of a UNDIRECTED graph -- that is the input 
 * will have symmetrical inital adjacency matrix.
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


struct edge {
    int from;
    int to;
};

#define ve std::vector < edge >
#define lseg std::list < edge >
#define sit std::set < lseg::iterator >
#define vit std::vector < lseg::iterator >
#define graphtp std::map< int, vit >  

void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(graphtp::const_iterator jt = g.begin(); jt != g.end(); jt++)
    {
        out("%d: ", jt->first);
        for(vit::const_iterator it = jt->second.begin(); it != jt->second.end(); ++it) {
            lseg::iterator lit = *it;
            out("(%d, %d) ", *lit);
        }
        out("\n");
    }
}

void print_alls(const lseg & alledges)
{
    for(lseg::const_iterator it = alledges.begin(); it != alledges.end(); ++it) 
        out("(%d, %d), ", it->from, it->to);
    out("\n");
}


//need genuine copy of the parameters
int mincut(graphtp incomming, graphtp outgoing, lseg alledges)
{
    while(incomming.size() > 2) {
        //pick edge randomly 
        int i = rand() % alledges.size();
        lseg::iterator it;
        for(it = alledges.begin(); it != alledges.end() && i > 0; it++, i--) ;
        edge eg = *it;
        out("merging eg(%d,%d), incomming.size() = %d\n", eg.from, eg.to, incomming.size());

        //remove eg.to from the graph, substitute all references to 
        
        //work with incomming
        {
            graphtp::iterator fit_i = incomming.find(it->to);
            assert(fit_i != incomming.end() && "not found in incomming");
            vit & t_i = fit_i->second;
            vit::iterator jt = t_i.begin(); 
            while(jt != t_i.end()) {
                if((*jt)->from == eg.from) //loop
                    jt = t_i.erase(jt);
                else {
                    (*jt)->to = eg.from;
                    incomming[eg.from].push_back(*jt);
                    jt++;
                }
            }
            incomming.erase(fit_i);
            out("After merging pair, incomming: ");
            print_graph(incomming);
        }
        out("After merging incomming, alls: ");
        print_alls(alledges); 

        //work with outgoing from it->from
        {
            graphtp::iterator fit_o = outgoing.find(it->from);
            assert(fit_o != outgoing.end() && "not found in outgoing");
            vit & t_o = fit_o->second;
            vit::iterator jt = t_o.begin(); 
            while(jt != t_o.end()) {
                if((*jt)->to == eg.to) //loop
                    jt = t_o.erase(jt);
                else {
                    jt++;
                }
            }
        }

        out("After merging outgoing from, alls: ");
        print_alls(alledges);
        
        //then work with outgoing from it->to
        {
            graphtp::iterator fit_o = outgoing.find(it->to);
            assert(fit_o != outgoing.end() && "not found in outgoing");
            vit & t_o = fit_o->second;
            vit::iterator jt = t_o.begin(); 
            while(jt != t_o.end()) {
                if((*jt)->from == eg.from) //loop
                    jt = t_o.erase(jt);
                else {
                    (*jt)->from = eg.from;
                    outgoing[eg.from].push_back(*jt);
                    jt++;
                }
            }
            outgoing.erase(fit_o);
            out("After merging pair, outgoing: ");
            print_graph(outgoing);
        }
        out("After merging pair, incomming again: ");
        print_graph(incomming);

        out("After merging outgoing to, alls: ");
        print_alls(alledges);

        alledges.erase(it);

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
    graphtp incomming;
    graphtp outgoing;
    lseg alledges;
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

        vit e;
        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            int nodeto = atoi(tok); 
            if(nodeto <= m && from != nodeto) {
                out("red tok='%s'\n", tok);

                graphtp::iterator it = incomming.find(nodeto);
                if(it == incomming.end()) {
                    vit b;
                    incomming[nodeto] = b;
                }

                if(from < nodeto) {
                    edge eg;
                    eg.from = from;
                    eg.to = nodeto;
                    alledges.push_front(eg);  //push_back()
                    lseg::iterator nn = alledges.begin();
                    e.push_back(nn); //end()--
                    
                    incomming.find(nodeto)->second.push_back(nn); //edges comming into 'to'
                }

            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }
            tok = strtok(NULL, " \n\t");
        }
        outgoing[from] = e; //edges going out of 'from'

        out("size of alledges %d\n", alledges.size());
    }


    printf("Case %d:\n", ++ord);
    out("Incomming: ");
    print_graph(incomming);
    out("Outgoing: ");
    print_graph(outgoing);
    print_alls(alledges);

    static timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);

    int allmin = 100000;
    int  mn;
    for(int i = 0; i < incomming.size()*incomming.size() ; i++) { //run n*n times
        mn = mincut(incomming, outgoing, alledges);
        printf("%d) min = %d allmin = %d\n", i, mn, allmin);
        if(allmin > mn) 
            allmin = mn;
    }
    printf("Tot mn = %d\n", allmin);

  }

  return 0;
}
