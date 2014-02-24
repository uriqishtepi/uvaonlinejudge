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
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



int main(int argc, char **argv)
{
    out("Starting...\n");

    char str[21] = {0};
    char *buff = NULL;
    size_t sz;
    int n;
    while(scanf("%d\n",&n) != EOF) {
        int rev = 0;
        forl(i, 0, 4) {
            ((char*)&rev)[i] = ((char*)&n)[3-i];
        }
        printf("%d converts to %d\n", n, rev);
    }
    return 0;
}
