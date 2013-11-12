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
#define mmi std::multimap<int, int>
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

    char * buff = NULL;
    int w, h, n;
    scanf("%d\n", &n);
    while( scanf("%d %d\n",&w,&h) != EOF && w != 0) {
        out("%d %d\n",w,h);
        w-=2; //ignore border cells
        h-=2;

        int x = (w/3) + (int)((w%3) > 0);
        int y = (h/3) + (int)((h%3) > 0); 
        out("tot in x = %d, tot in y = %d\n", 
                x,y);
        printf("%d\n", x*y);
    }
    return 0;
}

