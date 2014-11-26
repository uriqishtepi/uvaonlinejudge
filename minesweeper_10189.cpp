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
#include <assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

struct matrix {
    matrix(int  rows, int  cols) : _rows(rows), _cols(cols) { 
        out("rows %d, cols %d\n", rows, cols);
        assert(rows > 0);
        assert(cols > 0);
        _v.resize(rows * cols);
    }
    int & operator() (int  row, int  col) { 
        int  offset = row * _cols + col; 
        out("row %d, col %d, offset %d\n", row, col, offset);
        assert (row >= 0 && row < _rows); 
        assert (col >= 0 && col < _cols); 
        assert (offset < _v.size()); 
        return _v[offset]; 
    }
    void print() {
        forl(i, 0, _v.size()) {
            /*
            printf("%2d",_v[i]);
                */
            if(_v[i] > 9 )
                printf("*");
            else
                printf("%c", _v[i] + '0');
            if(((i+1) % _cols) == 0)
                printf("\n");
        }
    }

    private: 
        int _rows;
        int _cols;
        vi _v;
};


void setStar(matrix & M, int  m, int  n, int  r, int  c)
{
    assert(r >= 0);
    assert(r < m);
    assert(c >= 0);
    assert(c < n);
    out("setstar %d %d \n", r, c);

    int  minr = std::max(0, r-1);
    int  minc = std::max(0, c-1);
    int  maxr = std::min(m-1, r+1);
    int  maxc = std::min(n-1, c+1);

    out("range %d %d %d %d \n", minr, minc, maxr, maxc);
    forl(i, minr, maxr+1) {
        forl(j, minc, maxc+1) {
            out("setting %d %d \n", i,j);
            if(i == r && j == c)
                M(i, j) = '*';
            else 
                M(i, j)++;
        }
    }
    //M.print();
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int  m, n; //m rows, n columns
    int field = 0;
    while(1) {
        scanf("%d %d\n", &m, &n);
        out("%d %d\n", m, n);
        if(m == n && m == 0)
            return 0;

        assert(m > 0 && m <= 100);
        assert(n > 0 && n <= 100);
        field++;
        matrix M(m,n);
        size_t sz;
        int  counter = 0;
        char * buff = NULL;
        while(counter++ < m && getline(&buff, &sz, stdin) != -1) {
            assert(strlen(buff)-1 == n);
            forl(j, 0, n) {
                if(buff[j] == '*')
                    setStar(M, m, n, counter-1, j);
            }   
        }

        if(field > 1) printf("\n");
        printf("Field #%d:\n",field);
        M.print();
    }
}

