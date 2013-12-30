/* substring search
 * utilizes three way quicksort and suffix creation to produce a bigger list of 
 * substrings, thus the search will be extremely fast (binary search).
 *
 * can use this also for longest common substring, just search adjacent cells 
 * after sorting
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

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

int R = 256; //radix 2^8


inline
char charat(const std::string & s, int i)
{
    if(i < s.size()) return s.at(i);
    else return -1;
}

void insertion_sort(const std::vector<char *> & strings, std::vector<int> &v, int start, int end, int chrindx)
{
    for(int i = start; i < end - 1; i++){
        for(int j = i; j < end; j++) {
            if( strcmp(&strings[v[i]][chrindx], &strings[v[j]][chrindx]) > 0) {
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
            }
        }
    }

}



//pick a pivot, maybe randomly
//put all points above, less than and equal to in separate places of v[i]
void threeway_quicksort(const std::vector<char *> & strings, std::vector<int> &v, int start, int end, int chrindx)
{
    out("threeway_quicksort %d, %d, %d\n", start, end, chrindx);
    int n = end - start;
    if(n < 2) return;
    if(n < 20) { insertion_sort(strings, v, start, end, chrindx); return; }

    for(int i = start; i < end; i++) {
        out("h %s\n", strings[v[i]]);
    }

    //get the pivot
    int p = rand() % n;
    int c = charat(strings[v[start+p]],chrindx);
    out("p %d => c %c\n", start+p, c);

    int lessthan = start;
    int gtthan = end;
    int eqthan = 0;

    int i = start;
    while(i < gtthan) {
        int lc = charat(strings[v[i]],chrindx);
        out("i %d => lc %c\n", i, lc);
        if(lc < c)
        {
            int temp = v[lessthan];
            v[lessthan] = v[i];
            v[i] = temp;
            lessthan++;
            i++;
        }
        else if(lc > c)
        {
            gtthan--;
            int temp = v[gtthan];
            v[gtthan] = v[i];
            v[i] = temp;
        }
        else //equal
        {
            i++;
        }
    }

    out("lessthan %d\n", lessthan);
    out("gtthan %d\n", gtthan);
    out("gtthan - lessthan %d\n", gtthan - lessthan);

    for(int i = start; i < end; i++) {
        out("%d) strings[%d]=%s\n", i, v[i], strings[v[i]]);
    }

    threeway_quicksort(strings, v, start, lessthan, chrindx);
    threeway_quicksort(strings, v, lessthan, gtthan, chrindx + 1);
    threeway_quicksort(strings, v, gtthan, end, chrindx);
}

int binary_search(const std::vector<char *> & strings, std::vector<int> &v, char * str, int start, int end)
{
    out("binary_search %d, %d\n", start, end);
    if(end - start < 1) return -1;

    int mid = (start + end) / 2;
    int cmp = strcmp(strings[v[mid]], str);
    out("cmp %s, %s, %d\n", strings[v[mid]], str, mid);
    if(cmp < 0)
        return binary_search(strings, v, str, mid+1, end);
    else if(cmp > 0)
        return binary_search(strings, v, str, start, mid);
    else {
        return mid; //this is in fact a list of locations where the srch str appears
        //if we want all of them, we need to do a for loop forwards and backwards
        //to find them all
    }
}

int computesim(char*s1, char*s2)
{
    int len1 = strlen(s1);
    int i = 0;
    while(i < len1 && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return i;
}

//longest common substring
int lcs(const std::vector<char *> & strings, std::vector<int> &v)
{
    int maxlen = 0;
    int maxindex = 0;
    //search adjacent cells (after sortin) for the longest subsequence
    for(int i = 0; i < strings.size()-1; i++) {
        int llen = computesim(strings[v[i]],strings[v[i+1]]);
        if(maxlen < llen) {
            maxlen = llen;
            maxindex = i;
        }
    }

    printf("longes common substring is %s\n",strings[v[maxindex]]);
}


int main(void)
{
    out("starting ...\n");
    std::cout << " Three way quick sort " << std::endl;

    std::vector<char*> strings;

    int N = 0;

    //start from 
    char str[256] = {0};
    while( scanf("%s",&str) != EOF ) {
        char * copy = strdup(str);
        strings.push_back(copy);
        int len = strnlen(copy, 256);
        for(int i = 1; i < len-1; i++) {
            strings.push_back(&copy[i]);
        }
    }
    N = strings.size();

    std::vector<int> v(N); //map to sorted strings
    for(int i = 0; i < N; i++)
        v[i] = i; //all v's entries point to initial respective locations 

    threeway_quicksort(strings, v, 0, N, 0);

    out("SORTED strings\n");
    for(int i = 0; i < N; i++) {
        out ("%s\n", strings[v[i]]);
    }

    int f = binary_search(strings, v, str, 0, N);
    if(f > 0)
        printf("found %s\n", strings[v[f]]);
    else
        printf("Not found %s\n", str);

    lcs(strings, v);
    return 0;
}
