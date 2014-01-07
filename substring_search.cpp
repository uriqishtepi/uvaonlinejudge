/* ternary trie
 * this method of having a trie, makes better use of memory
 * each node will have three children, lessthan, equal, gtthan
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
        int loc = sequential_search(haystack, needle, counter);

        if(loc >=0 ) printf("found in location  %d after %d probes\n", loc, counter);
        else printf("NOT found after %d probes\n",counter);
    }

    return 0;
}
