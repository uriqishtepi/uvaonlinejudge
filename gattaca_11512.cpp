/* the goal of this problem is to find the longest repeating substring 
 * so one way to do it is to sort all the substrings, keep track of
 * the longest one and then count how many times it shows up 
 * (obviously two or more). 
 * Since we are sorting the array, that takes nlogn (where n is the strlen). 
 *
 * It could possibly be achieved with order N, by using two pointers, 
 * the second one moving ahead of the first finding char same value, 
 * then record length of how long is the same substring (like strcmp). 
 * Then you set the first ptr to the second, and continue from
 * begginning. Problem with this is that it will find the longest substring
 * but not how many times it shows up, so one needs to do another go
 * through the string to then find how many times it shows up. 
 * This second part can be done by building a FSM of the longest repeated 
 * substring that we found.
 *
 */
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
#include <iomanip>
#include <string.h>
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


int g_maxLen;
const char * g_maxPtr;


struct comparator {
 public:
    comparator(const char* s, size_t n) : m_str(s), m_n(n)
    {
        out("CONSTRUCTOR\n");
        g_maxLen = 0;
        g_maxPtr = NULL;
    }

    bool operator()(const char * pa, const char * pb) {
        const char * spa = pa;
        const char * spb = pb;
        int len = 0;
        while(*pa && *pb && *pa == *pb && len < m_n) {
            pa++;
            pb++;
            len++;
        }


        if(len > g_maxLen || (len == g_maxLen && strncmp(spa, g_maxPtr,len)<0))
        {
            out(" inc maxlen %d (<= len %d), ", g_maxLen, len);
            g_maxLen = len;
            g_maxPtr = spa;
        }

        out("maxlen=%d, cmp %c %c, determined by '%.*s' and '%.*s'\n", 
                g_maxLen, *spa, *spb, len+1, spa, len+1, spb);

        return (*pa < *pb);
    }

    const char * m_str;
    int m_n;
  //private: comparator(const comparator & c);
};

void find_smallest_repeating(char * str)
{
    char * maxPtr = NULL;
    size_t maxLen = 0;

    maxPtr = str + 1;
    maxLen = 3;
    size_t N = strnlen(str, 1000);

    //sort strs
    std::vector<const char*>v(N);
    forl(i, 0, N) v[i]=str+i;

    comparator cmp(str, N);
    std::sort(v.begin(), v.end(), cmp);


    for(std::vector<const char *>::iterator it = v.begin(); it != v.end(); ++it)
    {
        out("  %c (%d)", **it, *it);
    }
    out("\n");

    if(g_maxLen < 1) {
        printf("No repetitions found!\n");
        return;
    }
    
    //The comparator will give us the longest repeated substring, smaller 
    //than any other substring with the same length of repeititon
    //Now we just need to find how many times such string repeats
    
    out("maxlen = %d\n", g_maxLen);
    std::vector<const char*>::iterator it = std::find(v.begin(), v.end(), g_maxPtr);
    assert(it != v.end());
    out("Found g_maxPtr: %.*s (%d) \n", g_maxLen, *it, *it);
    std::vector<const char*>::iterator sit = it;

    int freq = 0; //compute freq of the maxPtr

    //the while loop counts *it as well
    while(it != v.end() && strncmp(g_maxPtr, *it, g_maxLen) == 0) {
        out("next *it: %.*s\n", g_maxLen, *it);
        freq++;
        it++;
    }

    //we dont know where in the range of same reps g_maxPtr fell
    //so count backwards too, until reaching begin or a different substring
    //v.begin will almost always be '\n', except for last line in file
    while(v.begin() <= --sit && strncmp(g_maxPtr, *sit, g_maxLen) == 0) {
        out("next *it: %.*s\n", g_maxLen, *sit);
        freq++;
    }

    printf("%.*s %d\n", g_maxLen, g_maxPtr, freq);
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    char *buff = NULL;
    size_t sz;
    int n;
    scanf("%d\n",&n);
    assert(1 <= n && n <= 100000);

    for(int i = 0; i < n; i++) {
        if(getline(&buff, &sz, stdin) < 0) return 0;
        out("buff=%s\n", buff);
        find_smallest_repeating(buff);
    }
    free(buff); //cleanup
    return 0;
}
