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
#include <stdint.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
void out(...) {}
#endif


#define forl(i,init, max) for(size_t i = init; i < max; i++) 
#define vi std::vector<int>
#define ve std::vector<edge>
#define vd std::vector<float>
#define mwp std::map<float, edge> //map weight and destination point 
#define mdi std::map<float, int>  //map float int
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


//row major, ie A(i,j) i rows, j columns, to traverse
//we walk the rows first, ie j moves fastest
struct matrix {
    matrix(int rows, int cols) : m_rows(rows), m_cols(cols), m_vec(m_rows*m_cols) 
    {
        forl(i, 0, m_vec.size()) {
            m_vec[i] = INFINITY;
        }
        /*
        forl(i, 0, m_sz) {
            operator()(i,i) = 0.0;
        }
        */
    }
    size_t getRows() {return m_rows;}
    size_t getCols() {return m_cols;}
    inline float & operator()(int a, int b) { 
        assert(a >= 0 && a < m_rows); 
        assert(b >= 0 && b < m_cols); 
        return m_vec[a*m_cols + b]; 
    }
    size_t m_rows;
    size_t m_cols;
    std::vector<float>m_vec;
};

void printMatrix(matrix & D)
{
    forl(i, 0, D.getCols()) { 
        out("%8d ", i);
    }
    out("\n");
    forl(i, 0, D.getRows()) { 
        forl(j, 0, D.getCols()) { 
            out("%8.2f ", D(i,j));
        }
        out("\n");
    }
}

void printM(vd & M)
{
    size_t size = M.size();
    forl(i, 0, size) { 
        out("%8.2f ", M[i]);
    }
    out("\n");
}


void checkSubset(matrix &A, matrix &D, int n, int thisn, int prevmask)
{
    uint32_t thisnshifted = (1 << thisn);
    if(prevmask & thisnshifted) return;

    int newmask = prevmask ^ thisnshifted;
    //for all nodes (except the 0th one), check path 
    for(int k = 0; k < n; k++) { // k is intermediate node
        out("thisn = %d, working with k=%d prevmask=%d\n", thisn, k, prevmask);
        if(k == thisn || ((1 << k) & prevmask) == 0) continue; //cant have same node repeat
        float a;
        out("-prevmask = %d, prevmask & -prevmask = %d\n", -prevmask, prevmask & -prevmask);
        if((prevmask & (-prevmask)) == prevmask) {
            a = D(0, k+1);
            out("a(D(0,k+1))=%f ",a);
        }
        else {
            a = A(k, prevmask); 
            out("a(A(k,prevmask))=%f ",a);
        }

        float d = D(k+1, thisn+1);
        float newdist = a + d;
        out("A(%d,%d) = %f, newdist = %f : A(%d, %d) or a %f + %f\n", thisn, newmask, A(thisn, newmask), newdist, k, prevmask, a, d);
        //this masks dist is prev dist plus lastnodo to this node
        if(A(thisn, newmask) > newdist) //ISSUE: d[thisn][newmask] is expensive to find
            A(thisn, newmask) = newdist;
    }
    out("\n");
#ifdef DEBUG
    printMatrix(A);
#endif
}



//iterate over all N choose N subsets (subsets with exactly N items)
//A matrix with the best distances with each node as the last node
//D matrix with node to node distances
//n is the number of nodes
//sz is the size of this subset
//k identifies the bit we are working on
//thisn is the currentnode we are working on
//mask is the parameter with the binary choices of other nodes in the path
void check_all_subsets(matrix &A, matrix &D, int n, int sz, int k, int thisn, uint32_t mask)
{
    if(k >= n)  
        return checkSubset(A, D, n, thisn, mask); 

    if(sz > 0) {
        mask |= (1 << k);  //set bit to 1
        check_all_subsets(A, D, n, sz-1, k+1, thisn, mask);
        mask &= ~(1 << k); //set bit to 0
    }
    if(n - k > sz) {
        mask &= ~(1 << k); //set bit to 0
        check_all_subsets(A, D, n, sz, k+1, thisn, mask);
    }

}



//A is a matrix with size (n, 1 << n)
//D is matrix with distances between any two points
//and n is the number of points in the dataset
//for size in 2:n
//  for i in all subsets
//    for k node in n
float travelingSalesman(matrix & A, matrix &D, size_t n)
{
    //node zero is the starting point
    //we loop for k from 1 to n for the sizes
    //   loop for l from 1 to n for the last node
    //for every possibility of the this node and last node
    //we need to produce all the subsets possible
    //keep track of what is selected in bitmask
    forl(sz, 2, n) {
        printf("sz=%d\n",sz);
        for(size_t i = 1; i < n; i++) { //i is this node
            //generate and check all subsets for this size, and for this node i
            check_all_subsets(A, D, n-1, sz-1, 0, i-1, 0);
        }
    }
    //for i in 1 n
    //if(mindist < A[i][111111])
    //    mindist = A[i][111111])
    float mindist = INFINITY;
    int mask = (1 << (n-1)) -1;
    forl(i,0,n-1) {
        float fullpath = A(i, mask) + D(0, i+1);
        if(mindist > fullpath)
            mindist = fullpath;
    }

    return mindist;
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
    vd x;
    vd y;

    //Read coordinates for the N nodes
    while(counter++ < n && scanf("%f", &i) != EOF&& scanf("%f", &j) != EOF)
    {
        out("i = %f, j = %f\n", i, j);
        x.push_back(i);
        y.push_back(j);
    }
    assert(x.size() == n && "should have n items");

    matrix D(n, n);
    printf("allocating %d floats\n", n * (1 << (n-1)));
    matrix A = matrix(n-1, (1 << (n-1)) ); //to be accessed by mask

    //compute distance matrix for each pair, dont include node 0
    for(size_t k = 0; k < n; k++) {
        for(size_t l = k+1; l < n; l++) {
            //distance squared really
            float dx = (x[k]-x[l]);
            float dy = (y[k]-y[l]);
            D(k,l) = sqrt(dx*dx + dy*dy);
            D(l,k) = D(k,l);
        }
    }
#ifdef DEBUG
    printMatrix(D);
    printMatrix(A);
#endif

    float dist = travelingSalesman(A, D, n);
    printf("dist = %f\n", dist);

    return 0;
}

