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
    int N;
    scanf("%d\n", &N);

    while( N-- > 0) 
    {
        int K; 
        scanf("%d\n", &K);
        out("%d\n", K);

        long long int answ = (K * 567 / 9 + 7492) * 235 / 47 - 498;
        printf("%d\n", (abs(answ) /10 )%10);
    }
    return 0;
}

