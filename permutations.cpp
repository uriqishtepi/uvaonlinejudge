#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



void print(std::vector<int> &v)
{
    //std::for_each(v.begin(), v.end(), std::cout);
    forl(i, 0, v.size())
        printf("%d",v[i]);
    printf("\n");
}

void swap(int &a, int &b)
{
    int tmp = b;
    b = a;
    a = tmp;
}

bool diagonal_conflict(int N, int k, std::vector<int> &v)
{
    //if any two queens are in the diagonal return true
    forl(i, 0, k) {
        //two queens are diagonal to each other if x and y deltas match.
        if( (v[i] - v[k]) == (k - i)) return true;
        if( (v[k] - v[i]) == (k - i)) return true;
    }
}


//find all the permutations of the n queens so they don't attack eachother
//this will generate permutations such as 1,2,3; 1,3,2; etc.
//it means that first qween should go in row 1, second in row 2, etc.
//(actually should be starting from zero in the explanation above)
void n_queens_problem (int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    //by starting for loop at k, we avoid redoing a previous permutation
    //(ie we avoid getting combinations)
    forl(i, k, N) {
        swap(v[k], v[i]); //swap k with i
        if(!diagonal_conflict(N, k, v)) n_queens_problem(N, k+1, v);
        swap(v[k], v[i]); //put k back where it was
    }
}



//permutation on N elements, there are N! ways:
//permutations does *not* repeat same number twice: 1 2 3, 1 3 2, ....
//initialize the v before getting here with the N items to permute
//these are solutions to n-rooks problem
void permutations(int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    //by starting for loop at k, we avoid redoing a previous permutation
    //(ie we avoid getting combinations)
    forl(i, k, N) {
        swap(v[k], v[i]); //swap k with i
        permutations(N, k+1, v);
        swap(v[k], v[i]); //put k back where it was
    }
}


//have S slots with mult choices for each slot
void multcombinations(int S, int k, std::vector<int> &v, int mult)
{
    if(k >= S) { print(v); return; }

    forl(i, 0, mult) {
        v[k] = i;
        multcombinations(S, k+1, v, mult);
    }
}


//combinations of N numbers, there are 2^N combinations
//each number i can be taken or not
void combinations(int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    v[k] = 0;
    combinations(N, k+1, v);
    v[k] = 1;
    combinations(N, k+1, v);
}


void printsubsets(std::vector<int> &v)
{
    //std::for_each(v.begin(), v.end(), std::cout);
    printf("{");
    bool first = true;
    forl(i, 0, v.size()) {
        if(v[i] == 1) {
            if(!first) printf(",");
            first = false;
            printf("%d",i+1);
        }
    }
    printf("}\n");
}


//get combinations, a 1 at position v[k] means we take the element
void subsets(int N, int k, std::vector<int> &v)
{
    if(k >= N) { printsubsets(v); return; }

    v[k] = 0;
    subsets(N, k+1, v);
    v[k] = 1;
    subsets(N, k+1, v);
}


void gray_combinations(int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    gray_combinations(N, k+1, v);
    v[k] = 1 - v[k];
    gray_combinations(N, k+1, v);
}




int main(int argc, char **argv)
{
    out("Starting...\n");

    forl(i, 0, 5)
        forl(j, 0, 2)
            printf("i=%d, j=%d\n", i, j);

    {
        printf("\nCombinations binary\n");
        int N = 5;
        std::vector<int> v(N);
        combinations(N, 0,  v);
    }

    {
        printf("\nCombinations n-ary \n");
        int S = 2; //slots
        int C = 3; //choices per slot
        std::vector<int> v(C);
        multcombinations(S, 0, v, C);
    }
    
    {
        printf("\nPermutations \n");
        int N = 3;
        std::vector<int> v(N);
        forl(i, 0, N)
            v[i] = i;   
        permutations(N, 0, v);
    }
    
    {
        printf("\nn Queens problem, with pruning \n");
        int N = 5;
        std::vector<int> v(N);
        forl(i, 0, N)
            v[i] = i;   
        n_queens_problem(N, 0, v);
    }

    {
        int N = 5;
        printf("\nAll subsets of %d items\n", N);
        std::vector<int> v(N);
        subsets(N, 0,  v);
    }

    {
        printf("\nGray's Combinations binary\n");
        int N = 5;
        std::vector<int> v(N);
        gray_combinations(N, 0,  v);
    }
}
