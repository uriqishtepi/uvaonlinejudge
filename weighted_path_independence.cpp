/* 
 * weighted path independence
 * there is a brute force way of trying every combination
 * (exponintial time), but a memozing optimal subproblems 
 * (dynamic programming) way is more efficient: linear time. 
 * 
 * We have nodes connected in a path and each node has
 * a weight, the problem is to select nonadjacent nodes
 * such that sum of selected node weights is maximized.
 *
 * w0 - w1 - w2 - w3 - w4
 *
 * so you can take {w0, w2, w4}, or {w1, w4} as examples.
 *
 * it seems that we would want to leave out only the node 
 * with the smallest weight, assuming there is a odd 
 * number of items
 *
 * recurrence of subproblems:
 * A[i,j] = max{ A[i,j-1], A[i,j-2]+Wj }
 *
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
void out(...) {}
#endif


#define forl(i,init, max) for(size_t i = init; i < max; i++) 
#define vi std::vector<int>
#define ve std::vector<edge>
#define vd std::vector<double>
#define mwp std::map<double, edge> //map weight and destination point 
#define mdi std::map<double, int>  //map double int
#define se std::set<edge, cmpedge>  //set of edges
#define graphtp std::vector< se >  //graph is a vector of maps -- the edges



struct edge {
    int from;
    int to;
    float weight;
    bool operator<(const edge & other) {
        out("****** operrator < \n");
        return this->weight < other.weight;
    }
};

struct cmpedge {
    bool operator()(const edge & a, const edge &b) {
        return a.weight < b.weight;
    }
};


struct matrix {
    matrix(int s) : m_sz(s), m_vec(s*s) 
    {
        forl(i, 0, m_vec.size()) {
            m_vec[i] = INFINITY;
        }
        forl(i, 0, m_sz) {
            operator()(i,i) = 0.0;
        }
    }
    size_t getCardinality() {return m_sz;}
    inline double & operator()(int a, int b) { return m_vec[a*m_sz + b]; }
    size_t m_sz;
    std::vector<double>m_vec;
};

inline void printVec(vi & v) {
    forl(j, 0, v.size()) 
        out("%d ", v[j]);
    out("\n");
}

double travelingSalesman(matrix &D, int n, int mask, int lastn, double dist)
{
    double locdist = INFINITY;
    for(int i = 0; i < n; i++) {
        int lmask = 1 << i;
        if( (mask & lmask) == 0) { //slot available to use
            double d = travelingSalesman(D, n, mask | lmask, 
                                         i, dist + D(i, lastn));
            if(locdist > d)
                locdist = d;
        }
    }
    if(INFINITY == locdist) {
        locdist = dist + D(lastn, 0); //closing the loop
        out("one cycle with dist %f\n", locdist);
    }
    return locdist;
}

void independentSets(vi &nodes, int start)
{
    //fill in the A matrix bottom up
    //matrix A(n.size(), n.size()); //NxN not needed
    vi A(nodes.size());
    vi P(nodes.size());

    A[0] = nodes[0];
    if(nodes[0] > nodes[1]) {
        A[1] = nodes[0];
        P[1] = 0;
    }
    else {
        A[1] = nodes[1];
        P[1] = 1;
    }
    forl(i,2,nodes.size()) {
        int prev = A[i-1];
        int sum = A[i-2] + nodes[i];
        if(prev > sum) {
            A[i] = prev;
            P[i] = i-1;
        }
        else {
            A[i] = sum;
            P[i] = i;
        }
    }

    printVec(A);
    printVec(P);
    printf("Max weight = %d\n", A.back());
    printf("Subset: ");
    int i = P.back();
    while(i >=0 ) {
        printf("%d ", i);
        if(i == P[i]) i = i-2;
        else i = P[i];
    }

}


int main(void)
{
    out("starting ...\n");
    std::cout << " Weighted Path Independent Sets " << std::endl;



    size_t n; //nodes
    scanf("%d\n", &n);
    out("n %d\n",n);
    size_t counter = 0;
    char * buff = NULL;

    //Read coordinates for the N nodes
    while(counter++ < n && getline(&buff, &n, stdin) != -1 )
    {
        vi nodes;
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        do {
            out("red tok='%s'\n", tok);
            int weight = atoi(tok);
            nodes.push_back(weight);
        } while((tok = strtok(NULL," \n\t")) > 0);

        printVec(nodes);
        independentSets(nodes, 0);
    }
    return 0;
}
