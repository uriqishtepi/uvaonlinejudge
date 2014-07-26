/* knapsack problem 
 * memoisation of solution to optimal subproblems (dynamic programming) 
 */
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include<stdio.h>
#include<assert.h>
#include <string.h>



#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



#define forl(i,init, max) for(int i = init; i < max; i++) 
#define si std::set<int>
#define mi std::map<int, int>
#define vi std::vector<int>
struct item {
    int value;
    int size;
};
#define vt std::vector<item>

inline void add_if_greaterval(mi &subValues, int currVal, int currSz)
{
    if(subValues[currSz] < currVal) {
        subValues[currSz] = currVal;
        out("subValues[%d] <- %d\n",currSz, currVal);
    }
}

int main (void)
{
    vt coll;

    int knap; //k size
    size_t numIt;//k numitems
    scanf("%d %d\n", &knap, &numIt);

    int val = 0;
    int size = 0;

    while(scanf("%d %d\n", &val, &size) != EOF) {
        item itm = {val, size};
        coll.push_back(itm);
    }
    printf("\nsize=%d\n",numIt);

    si subSizes;
    mi subValues;

    //answ is max of(pick this item, recurse, dont pick item recurse);

    for(vt::iterator jt = coll.begin(); jt != coll.end(); ++jt)
    {
        int currSz = jt->size;
        int currVal = jt->value;
        out("-----\nitem sz=%d val=%d\n", currSz, currVal);
        mi cpanswVal = subValues;

        for(mi::iterator it = subValues.begin(); it != subValues.end(); ++it) {
            int newSz = currSz + it->first;
            out("considering from subValues %d,%d\n", it->first);

            if(newSz > knap) continue;

            int newVal = currVal + it->second;
            add_if_greaterval(cpanswVal, newVal, newSz);
        }

        subSizes.insert(currSz); //add if it does not exist
        add_if_greaterval(cpanswVal, currVal, currSz); //should insert

        subValues = cpanswVal ;
    }

    assert(coll.size() == numIt);
    assert(subValues.size() > 0);

    int max = -1;
    for(mi::iterator it = subValues.begin(); it != subValues.end(); ++it)
        if(max < it->second) max = it->second;

    printf("Answer=%d\n", max);
    return 0;
}

