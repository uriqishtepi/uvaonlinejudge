/* substring search right to left search Boyer-Moore 
 * can skip several (up to M) characters when mismatch
 *  uses two for loops and when there is a mismatch it starts
 * the internal loop from end, so it can do time M * N 
 * worst case with M and N being the sizes of they haystack and needle

 * need to precompute location of the rightmost location for each letter
 * then when the mismatch is in the pattern move to it
 * if the mismatch is not in the pattern, skip entire pattern M chars
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

void compute_lastloc(int lastloc[256], char * str, int len)
{
    for(int i = 0; i < len; i ++) {
        char c = str[i];
        lastloc[c] = i;
    }
}


//return location where it was found, -1 if not found
//right to left search
int rl_search(char * haystack, char * needle, int & counter)
{ 
    int lastloc[256] = {0};
    int nlen = strlen(needle);
    compute_lastloc(lastloc, needle, nlen);

    int len = strlen(haystack);
    out("for '%s' with length %d ", needle, nlen);
    int skip = 0;

    for(int i = 0; i < len - nlen + 1; i += skip)
    { 
        skip = 0;
        for(int j = nlen - 1; j != -1; j--) {
            counter++;
            char c = haystack[i+j];
            int l = lastloc[c];
            out("cmp %d %d : %c %c\n",i + j, j, c, needle[j]);
            if(c != needle[j]) {
                if(l < 0)
                    skip += nlen;
                else if(l > j)
                    skip += l;
                else
                    skip += 1;

                break;
            }
        }

        if(skip == 0) {
            return i;
        }
    }

    return -1;
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
        int loc = rl_search(haystack, needle, counter);

        if(loc >=0 ) printf("found in location  %d after %d probes\n", loc, counter);
        else printf("NOT found after %d probes\n",counter);
    }

    return 0;
}
