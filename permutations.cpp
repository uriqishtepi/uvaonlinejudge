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

void multcombinations(int N, std::vector<int> &v, int mult)
{
    if(N < 0) { print(v); return; }

    forl(i, 0, mult) {
        v[N] = i;
        multcombinations(N-1, v, mult);
    }
}


void combinations(int N, std::vector<int> &v)
{
    if(N < 0) { print(v); return; }

    v[N] = 0;
    combinations(N-1, v);
    v[N] = 1;
    combinations(N-1, v);
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int N = 5;
    forl(i, 0, 5)
        forl(j, 0, 2)
            printf("i=%d, j=%d\n", i, j);

    {
        std::vector<int> v(N);
        combinations(N-1, v);
    }

    {
        std::vector<int> v(N);
        multcombinations(4, v, 3);
    }
}
