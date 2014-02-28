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

int blocks[] = { 
     0, 0, 0, 3, 3, 3, 6, 6, 6,
     0, 0, 0, 3, 3, 3, 6, 6, 6,
     0, 0, 0, 3, 3, 3, 6, 6, 6,
    27,27,27,30,30,30,33,33,33,
    27,27,27,30,30,30,33,33,33,
    27,27,27,30,30,30,33,33,33,
    54,54,54,57,57,57,60,60,60,
    54,54,54,57,57,57,60,60,60,
    54,54,54,57,57,57,60,60,60};


inline
bool canuse(int S, int k, int mult, std::vector<int> &v, std::vector<char> &board)
{
    out("k=%d board[k]='%d' v[k]=%d\n", k, board[k], v[k]);
    if(board[k] != '.' && board[k] != v[k]) {
        out("missmatch with board[k]=%d\n", board[k]);
        return false;
    }

    for(int i = k - mult; i >= 0; i-= mult)
        if(v[k] == v[i]) {
            out("verti missmatch with %d\n", v[i]);
            return false;
        }

    int low = (k / mult ) * mult;
    for(int i = k-1; i >= low; i--) {
        if(v[k] == v[i]) {
            out("horiz missmatch with %d\n", v[i]);
            return false;
        }
    }

    //need to ensure the group uniqueness of v[k] as well
    //find group where k falls, then for i 
    int base = blocks[k];
    forl(i, 0, 3) {
        forl(j, 0, 3) {
            int off = base + i*9 + j;
            if(off >= k) break;
            if(v[off] == v[k] ) { 
                out("group missmatch with pos off = %d, v[off]=%d\n", off, v[off]);
                return false;
            }
        }
    }

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


/*
  1, 2, 3, 4, 5, 6, 7, 8, 9,
 10,11,12,13,14,15,16,17,18,
 19,20,21,22,23,24,25,26,27,
 28,29,30,31,32,33,34,35,36,
 37,38,39,40,41,42,43,44,45,
 46,47,48,49,50,51,52,53,54,
 55,56,57,58,59,60,61,62,63,
 64,65,66,67,68,69,70,71,72,
 73,74,75,76,77,78,79,80,81,

    forl(i,0,9) {
        forl(j,1,10)
            printf("%2d,",((i*9+j-1)%9)/3);
        printf("\n");
    }
    printf("\n");

    forl(i,0,9) {
        forl(j,1,10)
            printf("%2d,",((i*9+j-1)/9)/3);
        printf("\n");
    }
    printf("\n");

    forl(i,0,9) {
        forl(j,1,10)
            printf("%2d,",(((i*9+j-1)%9)/3)*3 + 27*(((i*9+j-1)/9)/3));
        printf("\n");
    }
    printf("\n");


 */


int main(int argc, char **argv)
{
    out("Starting...\n");

    int t;
    char board[9][9];
    const int N = 9; //9x9 puzzle
    if(!scanf("%d\n",&t) || !(t > 0)) 
        return 0;
    forl(k, 0, t) 
    {
        g_nsol = 0;
        g_case++;       
        char *buff = NULL;
        size_t sz;
        std::vector<char> board(N*N);
        forl(i, 0, N) {
            if(getline(&buff, &sz, stdin) < 0) return 0;
            if(strnlen(buff, N) < N) { i--; continue; }
            forl(j, 0, N) {
                assert(buff[j] == '.' || (buff[j]-'0' > 0 && buff[j]-'0' <= N));
                if(buff[j] == '.')
                    board[i*N + j] = buff[j];
                else
                    board[i*N + j] = buff[j]-'0';
            }
        }
        std::vector<int> v(N*N);
        sudoku_problem(N*N, 0, N, v, board);
        printf("Case %d: %d\n",g_case,g_nsol);
    }


}
