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

    int  m, n; //m rows, n columns
    int item = 0;
    while(1) {
        scanf("%d\n", &n);
        out("%d\n",n);
        if(n == 0)
            return 0;

        assert(n > 0 && n <= 1000);
        vi l;
        size_t sz;
        int  counter = 0;
        int d=0;
        int c=0;
        int cents = 0;
        long long int s=0;
        while(counter < n && scanf("%d.%d\n",&d, &c) != EOF) {
            cents = 100*d + c;
            out("%d %d\n",counter, cents);
            assert(cents >= 0 && cents <=1000000);
            l.push_back(cents);
            s += cents;
            counter++;
        }
        out("counter %d s %lf\n", counter, s);
        long long int avg = s / counter;
        out("%d/%d = %d\n",s, counter, avg);

        long long int exch = 0;
        for(counter = 0; counter < n; counter++ ) {
            out("%d %d\n",counter, l[counter]);
            if(l[counter] < avg)
                exch += avg - l[counter];
        }
        //if(item++ > 0) printf("\n");
        c = exch % 100;
        d = exch / 100;
        printf("$%d.", d);
        if(c < 10)
            printf("0%d\n", c);
        else
            printf("%d\n", c);
    }
}

