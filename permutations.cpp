#include<stdio.h>
#include<math.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include <string.h>
#include <iomanip>

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


int generate_all_boards()
{
    forl(i, 0, 3)
        forl(j, 0, 3)
            forl(k, 0, 3)
            {}
                
}

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

//permutations does *not* repeat same number twice: 1 2 3, 1 3 2, ....
//initialize the v before getting here with the N items to permute
//these are solutions to n-rooks problem
void permutations(int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    //by starting for loop at k, we avoid redoing a previous permutation
    //(ie we avoid getting combinations)
    forl(i, k, N) {
        swap(v[k], v[i]);
        permutations(N, k+1, v);
        swap(v[k], v[i]);
    }
}


void multcombinations(int N, int k, std::vector<int> &v, int mult)
{
    if(k >= N) { print(v); return; }

    forl(i, 0, mult) {
        v[k] = i;
        multcombinations(N, k+1, v, mult);
    }
}


void combinations(int N, int k, std::vector<int> &v)
{
    if(k >= N) { print(v); return; }

    v[k] = 0;
    combinations(N, k+1, v);
    v[k] = 1;
    combinations(N, k+1, v);
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
        int N = 3;
        std::vector<int> v(N);
        multcombinations(N, 0, v, N);
    }
    
    {
        printf("\nPermutations \n");
        int N = 3;
        std::vector<int> v(N);
        forl(i, 0, N)
            v[i] = i;   
        permutations(N, 0, v);
    }
}
