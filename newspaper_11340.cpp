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
#define mli std::map<unsigned char, unsigned long long int>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define mss std::map<std::string, std::string>
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

    out("sizeof int %d\n", sizeof(int));
    out("sizeof long int %d\n", sizeof(long int));
    out("sizeof unsigned long int %d\n", sizeof(unsigned long int));
    out("sizeof long long %d\n", sizeof(long long));
    out("sizeof unsigned long long int %d\n", sizeof(unsigned long long int));

    char * buff = NULL;
    int count = 0;
    int m;
    scanf("%d\n", &m); //number of tests
    while(count++ < m) {
        int valhash[256] = {0};
        mli revmap;
        int K;
        scanf("%d\n", &K); //number of tests
        int numc =0;
        while(numc++ < K) {
            unsigned long long int d;
            unsigned char c;
            scanf("%c %lld\n", &c, &d);
            out("%c %lld\n", c, d);
            revmap[c] = (unsigned long long int) d;
        }

        int lines;
        scanf("%d\n", &lines);
        size_t n;

        unsigned long long int sum = 0;
        while(lines-- > 0) {
            getline(&buff, &n, stdin);
            forl(i,0,strlen(buff)) {
                unsigned long long int val = 0;
                mli::iterator it = revmap.find((unsigned char) buff[i]);
                if(it != revmap.end())
                    val = it->second;

                //accumulate into sum, val can be zero
                out("pre sum=%lld val=%lld\n",sum, val);
                sum = sum + val;
                out("post sum=%lld val=%lld\n",sum, val);
            }
        }

        printf("%.2f$\n",(double)sum/100.0);
    }

    return 0;
}

