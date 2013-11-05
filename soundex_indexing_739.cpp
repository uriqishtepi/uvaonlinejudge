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

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define msi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define mi std::map<int, int>
#define INF 1<<30;

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

int main(int argc, char **argv)
{
    out("Starting...\n");

    char str[21] = {0};
    int n, m, c;
    int counter = 0;
    while(scanf("%s\n", &str) != EOF)
    {
        counter++;
        out("In: %s\n", str);
        char ltr = str[0];
        forl(i,1,strnlen(str,sizeof(str)-1)) {
        }

        printf("%10.20s %14s","NAME","SOUNDEX CODE");
    }

    return 0;
}
