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


char N [10][5][4] = {
   {" - ", "| |", "   ", "| |", " - " }, /* 0 */
   {"   ", "  |", "   ", "  |", "   " }, /* 1 */
   {" - ", "  |", " - ", "|  ", " - " }, /* 2 */
   {" - ", "  |", " - ", "  |", " - " }, /* 3 */
   {"   ", "| |", " - ", "  |", "   " }, /* 4 */
   {" - ", "|  ", " - ", "  |", " - " }, /* 5 */
   {" - ", "|  ", " - ", "| |", " - " }, /* 6 */
   {" - ", "  |", "   ", "  |", "   " }, /* 7 */
   {" - ", "| |", " - ", "| |", " - " }, /* 8 */
   {" - ", "| |", " - ", "  |", " - " }, /* 9 */
};

//print portion of a number specified by level
//number is n, size of number is s
//hasMore determines whether a blank should follow
inline void printNum(char ** str, int lvl, int s, int n, bool hasMore)
{
    assert(n < 10 && n >= 0);
    assert(lvl < 5 && lvl >= 0);
    ((*str)++)[0] = N[n][lvl][0]; // L

    forl(i, 1, s+1) {
        ((*str)++)[0] = N[n][lvl][1]; // M
    }  
    ((*str)++)[0] = N[n][lvl][2]; // R
    if(hasMore) 
        ((*str)++)[0] = ' ';
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int s, rn; //s size, n number
    int item = 0;
    while(1) {
        scanf("%d %d\n", &s, &rn);
        out("%d %d\n",s, rn);

        if(s == 0 && rn == 0)
            return 0;

        assert(s > 0 && s < 11);
        assert(rn >= 0 && s < 100000000);
        vi digits;

        if(rn == 0)
            digits.push_back(rn);
        for(int n = rn; n > 0; n = n / 10) {
            digits.push_back(n%10);
        }
        std::reverse(digits.begin(), digits.end());
        forl(j, 0, 5) { // 5 sections
            char buf[1024]  = {0};
            char * str = buf;

            if(1 == j || 3 == j) {
                for(int d = 0; d < digits.size(); d++){
                    int val = digits[d];
                    printNum(&str, j, s, val, d != digits.size() - 1);
                }
                for(int k = 0; k < s; k++) {
                    printf("%s\n", buf);
                }
            }
            else {
                for(int d = 0; d < digits.size(); d++){
                    int val = digits[d];
                    printNum(&str, j, s, val, d != digits.size() - 1);
                }
                printf("%s\n", buf);
            }
        }
        printf("\n");
    }
}

