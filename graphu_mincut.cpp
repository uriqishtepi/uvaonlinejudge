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

struct llist {
    edge data;
    llist * next;
    llist * prev;
    int counter; //count of nodes in list
    llist() { //constructor -- create dummy node
        this.prev = NULL;
        this.next = NULL;
        this.edge.from = -1;
        this.edge.to = -1;
        this.counter = 0;
    }
    llist*insert(const edge &data) { //insert after this -- first el always dummy
        llist *n = new llist();
        n.next = this.next;
        n.prev = this;
        n.data = data;
        this.next = n;
        counter++;
    }
    llist*erase(llist *toerase) { // remove node from list -- leak node
        llist *prev = toerase.prev;
        assert(prev != NULL); //can not erase first node
        prev.next = toerase.next; //can be null
        toerase.prev = NULL; //reset
        toerase.next = NULL;
        assert(counter > 0);
        counter--;
    }
    int size() { return counter; }
    llist *nth(int n) { 
        assert(counter < n && "asking for element larger than counter");
        llist* l = this.next;
        for(; l != NULL && n > 0; l = l.next, i--) 
        { }
        assert(l != NULL && "reached the end of the list");
        return l;
    }
    void print() {
        llist* l = this.next;
        for(; l != NULL && n > 0; l = l.next, i--) 
            out("(%d, %d), ", l->data.from, l->data.to);
        out("\n");
    }
    llist *clone() {
        llist *n = new llist();
        for(llist* l = this.next; l != NULL; l = l.next) 
            n.insert(l->data);
        return n;
    }
};

struct edge {
    int from;
    int to;
};

#define ve std::vector < edge >
#define lseg std::list < edge >
#define vit std::vector < llist* >
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
            llist *l = *it;
            out("(%d, %d) ", l->data.from, l->data.to);
        }
        out("\n");
    }
}


//need genuine copy of the parameters
int mincut(llist * orig)
{
    llist * alledges = orig->clone();
    graphtp incomming;
    graphtp outgoing;

    
    for(llist* l = alledges.next; l != NULL; l = l.next) 
    {
        incomming[l->to].push_back(l);
        if(incomming[l->from].empty()) ;
        outgoing[l->from].push_back(l);
        if(outgoing[l->to].empty()) ;
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

            llist* l = alledges.nth(i);
            stays = l->data.from;
            goes = l->data.to;
            out("merging eg(%d,%d), incomming.size() = %d\n", stays, goes, incomming.size());
            out("1 erase (%d,%d)\n", stays, goes);
            alledges.erase(l);

        }

        //remove goes from the graph, substitute all references to 
        
        //work with incomming
        {
            graphtp::iterator fit_i = incomming.find(goes);
            assert(fit_i != incomming.end() && "not found in incomming");
            vit & t_i = fit_i->second;
            vit::iterator jt = t_i.begin(); 
            while(jt != t_i.end()) {
                llist * l = *jt;

                if (l->data.from != stays) {
                    l->to = stays;
                    if( l->to < l->from) {
                        swap( l->to , l->from) ;
                        outgoing[stays].push_back(l);
                    }
                    else
                        incomming[stays].push_back(l);
                    jt++;
                }
                else {
                    if(l->data.from == stays && l->data.from >= 0) { //loop
                        out("2 erase (%d,%d)\n", l->data.from, l->data.to);
                        alledges.erase(l);
                    }
                    jt = t_i.erase(jt);
                }
            }
            incomming.erase(fit_i);
            out("After merging pair, incomming: ");
            out("Incomming: "); print_graph(incomming);
            out("Outgoing: "); print_graph(outgoing);
        }
        out("After merging incomming, alls: ");
        alledges.print();

        //work with outgoing from stays
        {
            graphtp::iterator fit_o = outgoing.find(stays);
            if(fit_o != outgoing.end()) {
                vit & t_o = fit_o->second;
                vit::iterator jt = t_o.begin(); 
                while(jt != t_o.end()) {
                    llist * l = *jt;
                    if( l->data.to == goes) { //loop
                        if(l->data.from >= 0) {
                            out("3 erase (%d,%d)\n", l->data.from, l->data.to);
                            alledges.erase(l);
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
        alledges.print();
        
        //then work with outgoing from goes
        {
            graphtp::iterator fit_o = outgoing.find(goes);
            if(fit_o != outgoing.end()) {
                vit & t_o = fit_o->second;
                vit::iterator jt = t_o.begin(); 
                while(jt != t_o.end()) {
                    llist * l = *jt;
                    if(l->from == stays) { //loop
                        if(l->data.from >= 0) {
                            out("4 erase (%d,%d)\n", l->data.from, l->data.to);
                            alledges.erase(l);
                        }
                        jt = t_o.erase(jt);
                    }
                    else {
                        l->from = stays;
                        if( l->to < l->from) {
                            swap( l->to , l->from) ;
                            incomming[stays].push_back(l);
                        }
                        else
                            outgoing[stays].push_back(l);
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

        out("At the end: ");
        alledges.print();
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
    llist *alledges;
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
