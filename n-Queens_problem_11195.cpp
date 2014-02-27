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

int g_case = 0;
int g_nsol = 0;

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

inline
bool canuse(int k, std::vector<int> &v, char board[15][15])
{
    return(board[k][v[k]] == '.');
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

void n_queens_problem (int N, int k, std::vector<int> &v, char board[15][15])
{
    if(k >= N) { 
        g_nsol++;
        //print(v); 
        return; 
    }

    //by starting for loop at k, we avoid redoing a previous permutation
    //(ie we avoid getting combinations)
    forl(i, k, N) {
        swap(v[k], v[i]); //swap k with i
        if(canuse(k, v, board) && !diagonal_conflict(N, k, v)) 
            n_queens_problem(N, k+1, v, board);
        swap(v[k], v[i]); //put k back where it was
    }
}



int main(int argc, char **argv)
{
    out("Starting...\n");

    int n;
    char board[15][15];
    while(scanf("%d\n",&n) && n > 0) {
        g_nsol = 0;
        g_case++;       
        char *buff = NULL;
        size_t sz;
        forl(i, 0, n) {
            if(getline(&buff, &sz, stdin) < 0) return 0;
            forl(j, 0, n)
                board[i][j] = buff[j];
        }
        std::vector<int> v(n);
        forl(i, 0, n)
            v[i] = i;   
        n_queens_problem(n, 0, v, board);
        printf("Case %d: %d\n",g_case,g_nsol);
    }


}
