/* substring search using DFA -- knuth moris prat 
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



struct matrix {
    matrix(int rows, int cols) : _cols(cols), _rows(rows) 
    { _v.reserve(rows * cols); }
    int & operator()(int row, int col) { return _v[row * _cols + col]; }
    std::vector<int> _v;
    int _cols;
    int _rows;
};

void build_dfa(matrix & dfa, char * str)
{
    int finalst = strlen(str);

    int lastst = 0;
    dfa(str[0],0) = 1; //starting char moves to state 1

    for(int i = 1; i < finalst; i++) {
        for(int j = 0; j < 256; j++)
            dfa(j, i) = dfa(j, lastst);

        char c = str[i];
        dfa(c,i) = i + 1;
        lastst = dfa(c, lastst);
    }

}


int string_search(char * haystack, char * needle, int & counter)
{
    int len = strlen(haystack);
    int finalst = strlen(needle);
    matrix dfa(256, finalst);
    build_dfa(dfa, needle);

    int state = 0;
    int loc = -1;
    for(int i = 0; i < len; i++)
    {
        counter++;
        char c = haystack[i];
        if((state = dfa(c, state)) == finalst) {
            loc = i - state + 1;
            break;
        }
    }
    return loc;
}

//return location where it was found, -1 if not found
int sequential_search(char * haystack, char * needle, int & counter)
{ 
    int len = strlen(haystack);
    int nlen = strlen(needle);
    out("for '%s' with length %d ", needle, nlen);
    int loc = -1;

    for(int i = 0; i < len - nlen; i++) { 
        int j = 0;
        for(j = 0; j < nlen; j++) { 
            counter++;
            out("cmp %d %d : %c %c\n",i + j, j, haystack[i+j], needle[j]);
            if(haystack[i+j] != needle[j]) {
                break;
            }
        }

        if(j == nlen) {
            loc = i;
            break;
        }
    }


    return loc;
}

int main(void)
{
    out("starting ...\n");
    std::cout << " SubString search " << std::endl;

    char haystack[10000] = {0};
    char needle[256] = {0};
    scanf("%s\n",&haystack);
    out("searching in %s \n", &haystack);
    while(scanf("%s\n",&needle) != EOF) 
    { 
        int counter = 0;
        int loc = string_search(haystack, needle, counter);

        if(loc >=0 ) printf("found in location  %d after %d probes\n", loc, counter);
        else printf("NOT found after %d probes\n",counter);
    }

    return 0;
}
