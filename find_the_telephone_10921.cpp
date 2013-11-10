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

    mi rvmp;
    rvmp['A'] = 2;
    rvmp['B'] = 2;
    rvmp['C'] = 2;
    rvmp['D'] = 3;
    rvmp['E'] = 3;
    rvmp['F'] = 3;
    rvmp['G'] = 4;
    rvmp['H'] = 4;
    rvmp['I'] = 4;
    rvmp['J'] = 5;
    rvmp['K'] = 5;
    rvmp['L'] = 5;
    rvmp['M'] = 6;
    rvmp['N'] = 6;
    rvmp['O'] = 6;
    rvmp['P'] = 7;
    rvmp['Q'] = 7;
    rvmp['R'] = 7;
    rvmp['S'] = 7;
    rvmp['T'] = 8;
    rvmp['U'] = 8;
    rvmp['V'] = 8;
    rvmp['W'] = 9;
    rvmp['X'] = 9;
    rvmp['Y'] = 9;
    rvmp['Z'] = 9;

    int a, b;
    char * str = NULL;
    size_t n;

    while(getline(&str, &n, stdin) > 0) 
    {
        forl(i,0,strlen(str)) {
            //if(str[i] < 'A' || str[i] > 'Z')
            //    printf("%d",(str[i]+7)%10);
            mi::iterator it = rvmp.find(str[i]);
            if(it != rvmp.end())
                printf("%d",it->second);
            else printf("%c",str[i]);
        }
    }
    return 0;
}
