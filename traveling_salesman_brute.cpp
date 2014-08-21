/* Traveling salesperson problem: given a list of cities
 * fiind the shortest route (cycle) that goes through al the cities
 * only once.
 *
 * Brute force algorithm permutes the path:
 * 1) A B C D [A]
 * 2) A B D C [A]
 * 3) A C B D [A]
 * 4) A C D B [A]  - 2 backwards
 * 5) A D B C [A]  - 3 backwards
 * 6) A D C B [A]  - 1 backwards
 *
 *
 * We can build the full search by adding one city at a time, 
 * starting with A:
 *
 * 1) A
 *
 * path is zero. Then we add B. 
 *
 * 1) A B [A]
 *
 * path is D(A,B). Then we add C, still no variability yet:
 *
 * 1) A B C [A]
 * 2) A C B [A] - 1 backwards
 *
 * path is D(A,B) + D(B,C) + D(C, A) (forms triangle). 
 * Now things get a bit interesting, we add D:
 * 
 * 1) A B C D [A]   - from 1) A B C [A] add D between C [A]
 * 2) A B D C [A]   - from 1) A B C [A] add D between B C
 * 3) A D B C [A]   - from 1) A B C [A] add D between A B
 *
 * 4) A C B D [A]   - from 2) A C B  - same as 3) A D B C [A]
 * 5) A C D B [A]   - from 2) A C B  - same as 2) A B D C [A]
 * 6) A D C B [A]   - from 2) A C B  - same as 1) A B C D [A]
 *
 * so we isert D in between each edge in previous subproblem
 * it would be useful to remember D(A B C) because it is needed 
 * to compute D(A B C D)
 *
 * This is how we could remeber, we need array 2^N and encode 
 *   A 0001, B 0010, C 0100, D 1000
 * and then use OR to encode combinations:
 *   D(A,B) = A[A | B] = A [ 0001 | 0010 ] = A [ 0011 ]
 *
 * By doing so, we can in fact not store D(A B C D), 
 * D(A B D C) and D(A D B C) separately, but rather
 * we only store it as one entry D(1111), and store there
 * the shortest of the three mentioned.
 * However we do need to know the last node used, so we can
 * differentiate between D(A,B,C,D,E) and D(A,B,D,C,E) for
 * instance which matters only when computing the distance 
 * of the last added element E from the last D or C.
 *
 * Once we comput the smallest distance from A to E, we 
 * are free to forget all the nodes in between and only 
 * remember that E was last.
 *
 *
 * The brute force algorithm has to pick a starting vertex A,
 * and choose all combinations of walking the other points
 * (there should be n! of them):
 * A (N-1 choices) * (N-2 choices) * .... * (2 choices) * 1
 *
 *
 * We will read in points in a plane, compute the distances
 * as the weights, and then do analysis on complete graph 
 * based on weights.
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

//#define DEBUG true
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

void printMatrix(matrix & D)
{
    size_t size = D.getCardinality();
    forl(i, 0, size) { 
        forl(j, 0, size) { 
            out("%8.2f ", D(i,j));
        }
        out("\n");
    }
}



enum {white=0, gray=1, black=2,};

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


int main(void)
{
    out("starting ...\n");
    std::cout << " Traveling Salesman " << std::endl;

    size_t n; //nodes
    scanf("%d\n", &n);
    out("n %d\n",n);
    size_t counter = 0;
    float i, j;
    matrix D(n);
    vd x;
    vd y;

    //Read coordinates for the N nodes
    while(counter++ < n && scanf("%f %f", &i, &j) != EOF)
    {
        out("i = %f, j = %f\n", i, j);
        x.push_back(i);
        y.push_back(j);
    }
    assert(x.size() == n && "should have n items");

    //compute distance matrix for each pair
    for(size_t k = 0; k < n; k++) {
        for(size_t l = k+1; l < n; l++) {
            //distance squared really
            double dx = (x[k]-x[l]);
            double dy = (y[k]-y[l]);
            D(k,l) = sqrt(dx*dx + dy*dy);
            D(l,k) = D(k,l);
        }
    }
    //printMatrix(D);

    //keep track of what is selected in bitmask
    int mask = 1; //start with first node selected
    double dist = travelingSalesman(D, n, mask, 0, 0);
    printf("dist = %f\n", dist);

    return 0;
}
