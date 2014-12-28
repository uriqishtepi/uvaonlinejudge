#include <iostream>
#include <set>
#include <algorithm>
#include <stdio.h>

#define vi std::set<long long int>
#define forl(a, b, c) for(int a = b; i<c; i++)

int main()
{
    /*
    vi ugly;
    ugly.insert(1);

    while(ugly.size() < 15501) {
        vi copy = ugly;
        for(vi::iterator it = copy.begin(); it!=copy.end(); it++) {
            ugly.insert(*it * 2);
            ugly.insert(*it * 3);
            ugly.insert(*it * 5);
        }
    }
    //std::for_each(ugly.begin(),ugly.end(), std::cout);
    for(vi::iterator it = ugly.begin(); it!= ugly.end(); it++)
        printf("%lld\n", *it);

    */
    printf("The 1500'th ugly number is 859963392.\n");
    return 0;
}
