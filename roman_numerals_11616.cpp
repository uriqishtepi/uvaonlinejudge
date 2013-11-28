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
#define mci std::map<char, int>
#define mic std::map<int, char>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


//returns true if a is smaller than b
bool smaller(char a, char b)
{
    if(a == 'V' || a == 'L' || a == 'D')
        return false;

    if(a == 'I' && (b == 'V' || b == 'X'))
        return true;
    if(a == 'X' && (b == 'L' || b == 'C'))
        return true;
    if(a == 'C' && (b == 'D' || b == 'M'))
        return true;

    return false;
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    mci m;
    m['I'] = 1;
    m['V'] = 5;
    m['X'] = 10;
    m['L'] = 50;
    m['C'] = 100;
    m['D'] = 500;
    m['M'] = 1000;

    mic revm;
    for(mci::iterator it = m.begin(); it != m.end(); it++)
        revm[it->second] = it->first;


    char * buff = NULL;
    size_t n;
    int count = 0;

    while( getline(&buff, &n, stdin) != -1)
    {
        mci::iterator it = m.find(buff[0]);
        if(it == m.end()) { //int to roman
            int val = atoi(buff);
            std::string s;
            int thou = val / 1000;

            forl(i,0,thou)
                s += "M";
            val %= 1000;

            int hund = val / 100;
            while(hund) {
                if(hund > 8) { //CM
                    s += "CM";
                    hund = 0;
                }
                else if(hund > 4) {
                    s += "D";
                    hund -= 5;
                }
                else if(hund > 3) {
                    s += "CD";
                    hund = 0;
                }
                else if(hund > 0) {
                    s += "C";
                    hund -= 1;
                }
            }

            val %= 100;

            int tens = val / 10;
            while(tens) {
                if(tens > 8) {
                    s += "XC";
                    tens = 0;
                }
                else if (tens > 4) {
                    s += "L";
                    tens -= 5;
                }
                else if (tens > 3) {
                    s += "XL";
                    tens = 0;
                }
                else if(tens > 0) {
                    s += "X";
                    tens -= 1;
                }
            }

            val %= 10;

            while(val) {
                if(val > 8) {
                    s += "IX";
                    val = 0;
                }
                else if (val > 4) {
                    s += "V";
                    val -= 5;
                }
                else if (val > 3) {
                    s += "IV";
                    val = 0;
                }
                else if (val > 0) {
                    s += "I";
                    val -= 1;
                }
            }

            std::cout << s << std::endl;
        }
        else { //roman to int
            int sum = 0;
            int len = strlen(buff);
            forl(i,0,len) {
                int val = m[buff[i]];
                if(i<len-1 && smaller(buff[i],buff[i+1]))
                    sum -= val;
                else
                    sum += val;
            }
            printf("%d\n",sum);
        }
    }
    return 0;
}

