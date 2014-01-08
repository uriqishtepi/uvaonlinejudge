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



struct mydfa {
    mydfa(int rows, int cols, char * needle) : _cols(cols), _rows(rows)
    { 
        _v.reserve(rows * cols); 
        memset(_charmap, -1, sizeof(_charmap)/sizeof(int));
        _finalst = strlen(needle);

        _distinct = fillcharmap(needle);
        build_dfa(needle);
    }
    int & operator()(int row, int col) { return offset(row, col); }
    int & offset(int row, int col) { return _v[row * _cols + col]; }

    std::vector<int> _v;
    int _cols;
    int _rows;
    int _charmap[256];
    char _revmap[256];
    int _finalst;
    int _distinct;

    int finalst() { return _finalst; }
    void build_dfa(char * str)
    {
        int lastst = 0;
        offset(_charmap[str[0]],0) = 1; //starting char moves to state 1

        for(int i = 1; i < _finalst; i++) {
            for(int j = 0; j < _distinct; j++)
                offset(j, i) = offset(j, lastst);

            char c = str[i]; //_charmap[c] is the state corresponding to character c
            offset(_charmap[c],i) = i + 1;
            lastst = offset(_charmap[c], lastst);
        }
    }


    //fill a map of characters with a distinct id, return number of distinct characters
    //so aba wil have only 2 distinct character
    int fillcharmap(char * str)
    {
        int counter = 0;
        for(int i = 0; i < _finalst; i++) {
            if(_charmap[str[i]] < 0) {
                _revmap[counter] = str[i];
                _charmap[str[i]] = counter++;
            }
        }
        return counter;
    }


    void print()
    {
        for(int i = 0; i < _finalst; i++)
        {
            std::cout << _revmap[i] << " " ;
            for(int j = 0; j < _distinct; j++)
                std::cout << " " << offset(j, i);
            std::cout << std::endl;
        }
    }


};


int string_search(char * haystack, char * needle, int & counter)
{
    int len = strlen(haystack);
    int finalst = strlen(needle);

    mydfa dfa(256, needle);
    dfa.print();

    int state = 0;
    int loc = -1;
    for(int i = 0; i < len; i++)
    {
        counter++;
        char c = haystack[i];
        if((state = dfa(c, state)) == dfa.finalst()) {
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
