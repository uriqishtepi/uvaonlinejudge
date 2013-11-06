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
#define msi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define mi std::map<int, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


long long ff[21] = {0};

long long factorial(int n)
{
    if(n < 0) throw;
    if(ff[n] != 0) return ff[n];

    if(n == 1) ff[n] = 1;
    else if(n == 0) ff[n] = 1;
    else if(n == 2) ff[n] = 2;
    else
        ff[n] = n*factorial(n-1);
    return ff[n];
}
        

//there are len ways to pick the first, len-1 to the second...etc
//so there are len! combinations
//the (len-1)! first elements begin with the first letter: a
//the (len-1)! next elements begin with the second letter: b
//so, nth / (len-1) defines the first letter
int main(int argc, char **argv)
{
    out("Starting...\n");
    int n = 0;
    int counter = 0;
    scanf("%d\n", &n);
    while(n-- > 0)
    {
        long long nth = 0;
        char str[21] = {0};
        scanf("%s\n%ld\n",&str, &nth);
        out("%s %ld\n",str, nth);
        std::string srted (str);
        std::sort(srted.begin(),srted.end());
        std::string res;

        int len = strnlen(str,20);
        int index = 0;
        while(len > 0) 
        {
            long long fac = factorial(len-1);
            out("len = %d\n", len);
            out("fac = %d\n", fac);
            long long ratio = (int) (nth/fac);
            out("nth/fac = %d\n", ratio);
            out("first letter = %c\n", srted[ratio]);
            res.push_back(srted[ratio]);
            
            //need to work with the permutations of the remaining letters
            srted.erase(ratio, 1); 

            nth = nth % fac;
            len--;
            index++;
        }
        std::cout << res <<std::endl;

        counter++;
    }

    return 0;
}
