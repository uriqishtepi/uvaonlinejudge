/* substring search using DFA -- knuth moris prat 
 * version where we use all R characters (256 for ascii)
 * take time R * M to create the dfa
 * this version selects the distinct characters in M
 * so takes time proportional to M to create the dfa
 * it then takes time M + N to find for substrings
 * M is the size of the pattern (needle) a
 * nd N is the size of the text (haystack)
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
    mydfa(char * needle) 
    { 
        memset(_charmap, -1, sizeof(_charmap));
        _finalst = strlen(needle);
        out("processing needle='%s' with len %d\n", needle, _finalst);

        _distinct = fillcharmap(needle);
        _cols = _finalst;
        _rows = _distinct;
        _v.resize(_rows * _cols, 0); 
        assert(_v.size() == _rows * _cols && "size is bad");
        assert(_v.back() == 0 && "wrong val, not 0");
        assert(_v.front() == 0 && "wrong val, not 0");
        assert(_v[0] == 0 && "wrong val, not 0");

        build_dfa(needle);
    }

    int operator()(char c, int previous) { 
        int st = 0;
        if(_charmap[c] >= 0) st = state(_charmap[c], previous); 
        out("on %c state %d -> %d\n", c, previous, st);
        return st;
    }
    int & state(int row, int col) { return _v[row * _cols + col]; }
    int getOffset(int row, int col) { return row * _cols + col; }

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
        assert(_charmap[str[0]] < _distinct && "outside of range");
        out("_charmap[%d]=%d _v[o]=%d \n",str[0],_charmap[str[0]], _v[0]);
        state(_charmap[str[0]],0) = 1; //starting char moves to state 1

        for(int i = 1; i < _finalst; i++) {
            for(int j = 0; j < _distinct; j++)
                //offset(j, i) = offset(j, lastst);
                state(j,i) = state(j, lastst);

            char c = str[i]; //_charmap[c] is the state corresponding to character c
            state(_charmap[c],i) = i + 1;
            lastst = state(_charmap[c], lastst);
        }
    }


    //fill a map of characters with a distinct id, return number of distinct characters
    //so aba wil have only 2 distinct character
    int fillcharmap(char * str)
    {
        int counter = 0;
        for(int i = 0; i < 256; i++) {
            out("charmap[%d]=%d\n", i, _charmap[i]);
        }

        for(int i = 0; i < _finalst; i++) {
            char c = str[i];
            if(_charmap[c] < 0) {
                _revmap[counter] = c;
                _charmap[c] = counter++;
            }
            out("charmap[%c]=%d\n", c, _charmap[c]);
            assert(_revmap[_charmap[c]] == c && "not the same char");
        }
        return counter;
    }


    void print()
    {
        for(int j = 0; j < _distinct; j++)
        {
            std::cout << _revmap[j] << " " ;
            for(int i = 0; i < _finalst; i++) {
                std::cout << " " << _v[getOffset(j, i)];
                assert(state(j, i) == _v[getOffset(j,i)] && "not correct");
            }

            std::cout << std::endl;
        }
    }

};



int string_search(char * haystack, char * needle, int & counter)
{
    int len = strlen(haystack);

    mydfa dfa(needle);
    //dfa.print();

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
