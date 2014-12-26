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
#include <assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define vd std::vector<double>
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

    int n; 
    while(1) {
        scanf("%d\n", &n);
        out("%d\n",n);
        if(n == 0) return 0;
        assert(n > 0 && n <= 1000);
        vi l;
        int counter = 0;
        int d=0;
        int c=0;
        long long int s=0;
        while(counter < n && scanf("%d.%d\n",&d, &c) != EOF) {
            int cents = 100*d + c;
            assert(cents >= 0 && cents <=1000000);
            l.push_back( cents );
            out("%d %d.%.2d %d\n",counter, d,c, l.back());
            s += l.back();
            d = 0; 
            c = 0;
            counter++;
        }
        out("counter %d s %lld\n", counter, s);
        int avg = s / n;
        int needRound = (s % n) > 0;

        out("%lld/%d = %d\n", s, n, avg);

        int overpaid = 0;
        int underpaid = 0;
        for(counter = 0; counter < n; counter++ ) {
            if(avg < l[counter] )
                overpaid += l[counter] - (avg + needRound);
            else
                underpaid += avg - l[counter];
        }
        printf("$%.2f\n", std::max(underpaid, overpaid) / 100.0);
    }
}

