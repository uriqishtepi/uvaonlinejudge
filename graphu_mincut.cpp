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


void swap(int & a, int & b)
{
    int tmp = b;
    b = a;
    a = tmp;
}

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


//need genuine copy of the parameters
int mincut(lseg alledges)
{
    graphtp incomming;
    graphtp outgoing;
    for(lseg::iterator it = alledges.begin(); it != alledges.end(); ++it) 
    {
        incomming[it->to].push_back(it);
        if(incomming[it->from].empty()) ;
        outgoing[it->from].push_back(it);
        if(outgoing[it->to].empty()) ;
    }

    out("Incomming: "); print_graph(incomming);
    out("Outgoing: "); print_graph(outgoing);

    print_alls(alledges);

    while(incomming.size() > 2) {
        int stays = -1;
        int goes = -1;
        vit toerase;
        //pick edge randomly 
        {
            int i = rand() % alledges.size();
            lseg::iterator it;
            for(it = alledges.begin(); it != alledges.end() && i > 0; it++, i--) ;
            stays = it->from;
            goes = it->to;
            out("merging eg(%d,%d), incomming.size() = %d\n", stays, goes, incomming.size());
            out("1 adding to erase (%d,%d)\n", stays,goes);
            toerase.push_back(it);
        }

        //remove goes from the graph, substitute all references to 
        
        //work with incomming
        {
            graphtp::iterator fit_i = incomming.find(goes);
            if(fit_i == incomming.end())
               out("goes %d not found in incomming\n", goes);
            assert(fit_i != incomming.end() && "not found in incomming");
            vit & t_i = fit_i->second;
            vit::iterator jt = t_i.begin(); 
            while(jt != t_i.end()) {
                if((*jt)->from == stays) { //loop
                    bool found = false;
                    for(vit::iterator tit = toerase.begin(); tit != toerase.end(); tit++) if (*tit == *jt) { found = true; break; }
                    if(!found) {
                        out("2 adding to erase (%d,%d)\n", (*jt)->from,(*jt)->to);
                        toerase.push_back(*jt);
                    }
                    jt = t_i.erase(jt);
                }
                else {
                    out("1 was (%d,%d) -> (%d,%d)\n", (*jt)->from, (*jt)->to, (*jt)->from, stays);
                    (*jt)->to = stays;
                    if( (*jt)->to < (*jt)->from) {
                        swap( (*jt)->to , (*jt)->from) ;
                        outgoing[(*jt)->from].push_back(*jt);
                    }
                    else
                        incomming[stays].push_back(*jt);
                    jt++;
                }
            }
            incomming.erase(fit_i);
            out("After merging pair, incomming: ");
            out("Incomming: "); print_graph(incomming);
            out("Outgoing: "); print_graph(outgoing);
        }
        out("After merging incomming, alls: ");
        print_alls(alledges); 

        //work with outgoing from stays
        {
            graphtp::iterator fit_o = outgoing.find(stays);
            if(fit_o != outgoing.end()) {
                vit & t_o = fit_o->second;
                vit::iterator jt = t_o.begin(); 
                while(jt != t_o.end()) {
                    if( (*jt)->to == goes) { //loop
                        bool found = false;
                        for(vit::iterator tit = toerase.begin(); tit != toerase.end(); tit++) if (*tit == *jt) { found = true; break; }
                        if(!found) { 
                            out("3 adding to erase (%d,%d)\n", (*jt)->from,(*jt)->to);
                            toerase.push_back(*jt);
                        }
                        jt = t_o.erase(jt);
                    }
                    else {
                        jt++;
                    }
                }
            }
            else
                out("not found in outgoing stays %d\n", stays);
        }

        out("After merging outgoing from, alls: ");
        print_alls(alledges);
        
        //then work with outgoing from goes
        {
            graphtp::iterator fit_o = outgoing.find(goes);
            if(fit_o != outgoing.end()) {
                vit & t_o = fit_o->second;
                vit::iterator jt = t_o.begin(); 
                while(jt != t_o.end()) {
                    if((*jt)->from == stays) { //loop
                        bool found = false;
                        for(vit::iterator tit = toerase.begin(); tit != toerase.end(); tit++) if (*tit == *jt) { found = true; break; }
                        if(!found) {
                            out("4 adding to erase (%d,%d)\n", (*jt)->from,(*jt)->to);
                            toerase.push_back(*jt);
                        }
                        jt = t_o.erase(jt);
                    }
                    else {
                        out("2 was (%d,%d) -> (%d,%d)\n", (*jt)->from, (*jt)->to, stays, (*jt)->to);
                        (*jt)->from = stays;
                        if( (*jt)->to < (*jt)->from) {
                            swap( (*jt)->to , (*jt)->from) ;
                            incomming[(*jt)->to].push_back(*jt);
                        }
                        else
                            outgoing[stays].push_back(*jt);
                        jt++;
                    }
                }
                outgoing.erase(fit_o);
            }
            else
                out("not found in outgoing goes %d\n", goes);

            out("After merging pair, outgoing: ");
            out("Incomming: "); print_graph(incomming);
            out("Outgoing: "); print_graph(outgoing);
        }

        for(vit::iterator jt = toerase.begin(); jt != toerase.end(); ++jt) 
            alledges.erase(*jt);

        out("After removingall: ");
        print_alls(alledges);
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


    static timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);

    int allmin = 100000;
    int  mn;
    for(int i = 0; i < counter*counter ; i++) { //run n*n times
        mn = mincut(alledges);
        out("%d) min = %d allmin = %d\n", i, mn, allmin);
        if(allmin > mn) 
            allmin = mn;
    }
    printf("Case %d: %d\n", ++ord, allmin);
  }

  return 0;
}
