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
        if(n == 0)
            return 0;

        assert(n > 0 && n <= 1000);
        vd l;
        int counter = 0;
        float f=0;
        double s=0;
        while(counter < n && scanf("%f\n",&f) != EOF) {
            out("%d %f\n",counter, f);
            assert(f >= 0 && f <=10000);
            l.push_back(f);
            s += f;
            counter++;
        }
        out("counter %d s %lf\n", counter, s);
        double avg = s / counter;
        /*
        long long unsigned int u = avg*100;
        avg = u;
        avg = avg / 100;
        */
        out("%lf/%d = %lf\n",s, counter, avg);

        double overpaid = 0;
        double underpaid = 0;
        for(counter = 0; counter < n; counter++ ) {
            double diff = ((int) ((avg - l[counter])*100) ) / 100.0;
            //double diff = avg - l[counter];
            out("%d %f %f\n",counter, l[counter], diff);
            if(diff < 0) overpaid -= diff;
            else underpaid += diff;
        }

        //if(item++ > 0) printf("\n");
        //printf("$%.2lf\n", exch);
        printf("$%.2lf\n", std::max(underpaid, overpaid));
    }
}

