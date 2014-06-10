/* ccmpute the min cut of a UNDIRECTED graph -- that is the input 
 * will have symmetrical inital adjacency matrix.
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <list>
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


struct edge {
    int from;
    int to;
};

#define ve std::vector < edge >
#define lseg std::list < edge >
#define sit std::set < lseg::iterator >
#define si std::set < int >
#define vit std::vector < lseg::iterator >
#define graphtp std::map< int, vit >  


void swap(int & a, int & b)
{
    int tmp = b;
    b = a;
    a = tmp;
}

#ifdef DEBUG
void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(graphtp::const_iterator jt = g.begin(); jt != g.end(); jt++)
    {
        out("%d: ", jt->first);
        for(vit::const_iterator it = jt->second.begin(); it != jt->second.end(); ++it) {
            lseg::iterator lit = *it;
            out("(%d, %d) ", lit->from, lit->to);
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
#else
#define print_graph
#define print_alls
#endif


lseg::iterator getRandEdge(lseg & alledges)
{
    int i = rand() % alledges.size();
    lseg::iterator it;
    for(it = alledges.begin(); it != alledges.end() && i > 0; it++, i--) ;
    return it;
}



//for all iterateors in it list, if node->to is goes, replace with stays
//if node->from is stays and node->to is goes, delete as is loop
void fixConnected(graphtp & g, lseg & alledges, int orignode, int stays, int goes)
{

    vit & itlist = g.find(orignode)->second;

    out("fixConnected ( %d ) : vector of conts ex from (%d,x)\n", orignode, (*itlist.begin())->from);
    assert(!itlist.empty() && "vector of iterators can not be empty, we got here because goes has a connection to this node (orignode)");

    vit::iterator it = itlist.begin(); 
    while(it != itlist.end()) {
        lseg::iterator & nodeit = *it;
        if(nodeit->to != goes && nodeit->from != goes) {
            out("fixConnected not relevant (%d,%d)\n",nodeit->from,nodeit->to);
            ++it;
            continue;
        }


        if((nodeit->to == goes && nodeit->from == stays) ||  
           (nodeit->from == goes && nodeit->to == stays) ) { //loop
            out("loop on (%d,%d)\n", nodeit->from, nodeit->to);
            alledges.erase(nodeit);
            it = itlist.erase(it);
            continue;
        }

        out("fixConnected %d: working on (%d,%d)\n",orignode,nodeit->from,nodeit->to);

        out("%d: (%d,%d) turning %d -> %d\n", orignode, nodeit->from, nodeit->to, goes, stays);
        if(nodeit->to == goes)
            nodeit->to = stays;
        else 
            nodeit->from = stays;

        if( nodeit->to < nodeit->from) {
            swap( nodeit->to , nodeit->from) ;
        }
        g[stays].push_back(nodeit);
        ++it;
    }
    out("After merging pair, incomming: ");
    out("furst pass: "); print_graph(g);

    out("After merging incomming, alls: ");
    print_alls(alledges); 
}


//need genuine copy of the parameters
int mincut(lseg alledges)
{
    graphtp g; //populate the graph with pointers to alledges
    for(lseg::iterator it = alledges.begin(); it != alledges.end(); ++it) 
    {
        g[it->to].push_back(it);
        g[it->from].push_back(it);
    }

    out("g: "); print_graph(g);
    print_alls(alledges);

    while(g.size() > 2) {
        int stays = -1;
        int goes = -1;
        //pick edge randomly 
        
        lseg::iterator ersit = getRandEdge(alledges);
        stays = ersit->from;
        goes = ersit->to;
        out("\nMerging eg(%d,%d), %d -> %d, g.size() = %d\n", stays, goes, goes, stays, g.size());

        //remove goes from the graph, substitute all references to 
        
        //work with node that goes first, replace it with stays
        graphtp::iterator eras_it = g.find(goes);
        if(eras_it == g.end())
           out("goes %d not found \n", goes);
        assert(eras_it != g.end() && "not found in incomming");
        out("goes %d: eras_it key is (%d,x)\n",goes, eras_it->first);

        
        si nodelistcopy;
        for(vit::iterator v_it = eras_it->second.begin(); 
                    v_it != eras_it->second.end(); ++v_it)
        {
            lseg::iterator & con_edge = (*v_it);
            out("goes %d: conn_edge is (%d,%d)\n", goes, con_edge->from, con_edge->to);
            assert( (con_edge->from == goes || con_edge->to == goes) && "one of the nodes is not same as goes");
            assert( (con_edge->from != con_edge->to) && "From and to are same");
            
            //find if goes is from or to in link (for (1,3) can be 0,3 or 3,4
            int worknode;
            if(con_edge->from == goes)
                worknode = con_edge->to;
            else
                worknode = con_edge->from;

            assert(worknode != goes && "worknode can not be goes");

            nodelistcopy.insert(worknode);
        }


        //for every item connected to g[goes], do work in fixConnected
        for(si::iterator work = nodelistcopy.begin(); 
                    work != nodelistcopy.end(); ++work)
        {
            //work on list of nodes
            fixConnected(g,  alledges, *work, stays, goes); 
        }

        g.erase(eras_it);

        out("final pass g: "); print_graph(g);
        out("final all: "); print_alls(alledges);
        out("\n");
    }

    //whatever is left is the cut
    return alledges.size();
}


int main(void)
{
  out("starting ...\n");

  int N; //test cases
  scanf("%d\n", &N);
  out("N %d\n",N);
  int ord = 0;
    
  while(N-- > 0) {
    char * buff = NULL;
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

                if(from < nodeto) {
                    edge eg;
                    eg.from = from;
                    eg.to = nodeto;
                    alledges.push_front(eg);  //push_back()
                    lseg::iterator nn = alledges.begin();
                    e.push_back(nn); //end()--
                }

            }
            else {
                printf("ERROR: node %d outside of range (max %d)\n", nodeto,m);
            }
            tok = strtok(NULL, " \n\t");
        }

        out("size of alledges %d\n", alledges.size());
    }


    /*
    static timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);
    */

    int allmin = 100000;
    int  mn;
    for(int i = 0; i < counter*counter ; i++) { //run n*n times
        mn = mincut(alledges);
        printf("%d) min = %d allmin = %d\n", i, mn, allmin);
        if(allmin > mn) 
            allmin = mn;
    }
    printf("Case %d: %d\n", ++ord, allmin);
  }

  return 0;
}
