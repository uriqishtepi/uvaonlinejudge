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

char M [10][6] = {
   "hb bh", /* 0 */
   " r r ", /* 1 */
   "hrhlh", /* 2 */
   "hrhrh", /* 3 */
   " bhr ", /* 4 */
   "hlhrh", /* 5 */
   "hlhbh", /* 6 */
   "hr r ", /* 7 */
   "hbhbh", /* 8 */
   "hbhrh", /* 9 */
};

void printNum(int lvl, int s, int n, bool hasMore)
{
    assert(n < 10 && n >= 0);
    assert(lvl < 5 && lvl >= 0);
    forl(i, 0, s+2) {
        if(M[n][lvl] == 'h' && i !=0 && i != s+1) {
            printf("-");
        }
        else if( (M[n][lvl] == 'l' || M[n][lvl] == 'b')  && i == 0)
            printf("|");
        else if( (M[n][lvl] == 'r' || M[n][lvl] == 'b')  && i == s+1)
            printf("|");
        else
            printf(" ");
    }  
    if(hasMore) printf(" ");
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int s, rn; //s size, n number
    int item = 0;
    while(1) {
        scanf("%d %d\n", &s, &rn);
        out("%d %d\n",s, rn);
        assert(s > 0 && s < 11);
        vi digits;

        if(s == 0)
            return 0;

        if(rn == 0)
            digits.push_back(rn);
        for(int n = rn; n > 0; n = n / 10) {
            digits.push_back(n%10);
        }
        std::reverse(digits.begin(), digits.end());
        forl(j, 0, 5) {
            if(1 == j || 3 == j) {
                for(int k = 0; k < s; k++) {
                    for(int d = 0; d < digits.size(); d++){
                        int val = digits[d];
                        printNum(j, s, val, d != digits.size() - 1);
                    }
                    printf("\n");
                }
            }
            else {
                for(int d = 0; d < digits.size(); d++){
                    int val = digits[d];
                    printNum(j, s, val, d != digits.size() - 1);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
}
