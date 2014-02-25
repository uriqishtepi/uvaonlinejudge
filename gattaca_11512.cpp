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

#define DEBUG true
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

    bool operator()(int a, int b) {
        assert(a < m_n);
        assert(b < m_n);
        const char*pa = m_str+a;
        const char*pb = m_str+b;
        int len = 0;
        while(*pa && *pb && *pa == *pb && len < m_n) {
            pa++;
            pb++;
            len++;
        }

        out("maxlen=%d, cmp %d %d, determined by %.*s %.*s\n", 
                g_maxLen, a, b, len+1, m_str+a, len+1, m_str+b);

        if(len > g_maxLen) {
            out(" inc maxlen %d (<= len %d), ", g_maxLen, len);
            g_maxLen = len;
            g_maxPtr = pa;
        }

        out(" maxlen=%d, cmp %d %d, determined by %c %c\n", g_maxLen, a, b, *pa, *pb);
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
    size_t N = strlen(str);
    assert(1 <= N && N <= 1000);

    //sort strs
    std::vector<int>v(N);
    forl(i, 0, N) v[i]=i;

    comparator cmp(str, N);
    std::sort(v.begin(), v.end(), cmp);

    forl(i, 0, N) out("%d ", v[i]);
    out("\n");

    for( std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        out("%c\n", str[*it]);
    }
    
    //find longest repeating
    out("maxlen = %d\n", g_maxLen);
    int freq = 0; //compute freq of the maxPtr

    if(g_maxLen < 2)
        printf("No repetitions found!\n");
    else
        printf("%.*s %d\n", g_maxLen, g_maxPtr, freq);
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    char str[21] = {0};
    char *buff = NULL;
    size_t sz;
    int n;
    scanf("%d\n",&n);
    assert(1 <= n && n <= 100);

    for(int i = 0; i < n; i++) {
        if(getline(&buff, &sz, stdin) < 0) return 0;
        out("buff=%s\n", buff);
        find_smallest_repeating(buff);
    }
    return 0;
}
