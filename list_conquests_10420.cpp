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
    size_t n;
    int counter = 0;
    char * buff = NULL;
    float lastspeed = 0;
    float lasttime = 0;
    float lastdist = 0;

    msi counts;
    getline(&buff, &n, stdin);

    while(getline(&buff, &n, stdin) > 0) 
    {
        int h, m, s, speed = -1;
        char country[30]={0};
        sscanf(buff, "%s ",&country);
        
        counts[country]++;
    }
    for(msi::iterator it = counts.begin();it!=counts.end();++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    free(buff);
    return 0;
}
