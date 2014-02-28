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
#include <math.h>
#include <stdio.h>
#include <assert.h>

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
bool canuse(int S, int k, int mult, std::vector<int> &v, std::vector<char> &board)
{
    out("k=%d board[k]='%c' v[k]=%d\n", k, board[k], v[k]);
    if(board[k] != '.' && board[k] != v[k]) {
        out("missmatch with board %d\n", board[k]);
        return false;
    }

    for(int i = k - mult; i >= 0; i-= mult)
        if(v[k] == v[i]) {
            out("verti missmatch with %d\n", v[i]);
            return false;
        }

    int low = (k / mult ) * mult;
    for(int i = k-1; i >= low; i--)
        if(v[k] == v[i]) {
            out("horiz missmatch with %d\n", v[i]);
            return false;
        }

    //need to ensure the group uniqueness of v[k] as well
    //find group where k falls, then for i 
    return true;
}

//variant of the multi combination
//S is the size of the square board, mult is the size of the side of the square
void sudoku_problem(int S, int k, int mult, std::vector<int> &v, std::vector<char> &board)
{
    out("sudoku_problem k=%d mult=%d\n", k, mult);
    //print(v); 

    //k will start at 0 and go all the way to S - 1 and fill v[k]
    if(k >= S) { 
        g_nsol++;
        print(v); 
        return; 
    }

    forl(i, 0, mult) {
        v[k] = i+1; 
        bool rc = canuse(S, k, mult, v, board);
        out("i=%d rc=%d\n", i, rc);
        if(rc)
            sudoku_problem(S, k+1, mult, v, board);
    }
    v[k] = 0;
}



int main(int argc, char **argv)
{
    out("Starting...\n");

    int n;
    char board[15][15];
    while(scanf("%d\n",&n) && n > 0) {
        g_nsol = 0;
        g_case++;       
        std::vector<char> board(n*n);
        char *buff = NULL;
        size_t sz;
        forl(i, 0, n) {
            if(getline(&buff, &sz, stdin) < 0) return 0;
            forl(j, 0, n) {
                assert(buff[j] == '.' || (buff[j]-'0' > 0 && buff[j]-'0' <= n));
                if(buff[j] == '.')
                    board[i*n + j] = buff[j];
                else
                    board[i*n + j] = buff[j]-'0';
            }
        }
        std::vector<int> v(n*n);
        sudoku_problem(n*n, 0, n, v, board);
        printf("Case %d: %d\n",g_case,g_nsol);
    }


}
