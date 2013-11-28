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
#include <string.h>
#include <iomanip>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define mci std::map<char, int>
#define mic std::map<int, char>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


//returns true if a is smaller than b
long long int count_occ(int n)
{
    long long int count = 1;
    while(n != 1) {
        out("n = %d\n",n);
        if(n & 0x1) {
            n += (n << 1) + 1;
        }
        else n = n >> 1;
        count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    char * buff = NULL;
    int count = 0;
    int m, n;
    out("count for %d = %d\n",22,count_occ(22));

    while(scanf("%d %d", &m, &n) != EOF)
    {
        long long int val = 0;
        forl(i,std::min(m,n),std::max(m,n)+1)
            val = std::max(val, count_occ(i));
        printf("%d %d %ld\n",m,n,val);
    }
    return 0;
}

