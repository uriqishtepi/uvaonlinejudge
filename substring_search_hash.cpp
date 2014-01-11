/* substring search using hash of the pattern and computing
 * ongoing hash of the text so that you never have to backup
 * this is the rabin karp method
 *
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

int compute_hash(char * str, int base, int len, int key)
{
    int h = 0;
    for(int i = 0; i < len; i ++) {
        h = (h * base + str[i]) % key;
    }
    return h;
}


//return location where it was found, -1 if not found
//right to left search
int fingerprint_hash_search(char * haystack, char * needle, int & counter)
{ 
    int nlen = strlen(needle);
    int hashkey = 1111997; //prime number
    int RtoNLEN = 1;
    int base = 10;
    int pattrn = compute_hash(needle, base, nlen, hashkey);

    out("for '%s' with length %d \n", needle, nlen);
    for(int i = 1; i < nlen; i++) {
        RtoNLEN = (RtoNLEN * base) % hashkey;
    }
    out("pattrn '%d' \n", pattrn);

    int len = strlen(haystack);
    int runninghash = compute_hash(haystack, base, nlen, hashkey);
    out("runninghash '%d' \n", runninghash);

    counter++;
    if(runninghash == pattrn && strncmp(needle, haystack, nlen) == 0) {
        return 0;
    }

    for(int i = nlen; i < len; i++)
    { 
        counter++;

        runninghash = (runninghash  + hashkey - haystack[i - nlen] * RtoNLEN % hashkey) % hashkey;
        runninghash = (runninghash * base + haystack[i] ) % hashkey;
        out("runninghash '%d' \n", runninghash);

        if(runninghash == pattrn && strncmp(needle, haystack + i - nlen + 1, nlen) == 0) {
            return i-nlen + 1;
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
        int loc = fingerprint_hash_search(haystack, needle, counter);

        if(loc >=0 ) printf("found in location  %d after %d probes\n", loc, counter);
        else printf("NOT found after %d probes\n",counter);
    }

    return 0;
}
