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

int main(int argc, char **argv)
{
    out("Starting...\n");
    unsigned char code[99] = {0};
    code['B'] = '1';
    code['P'] = '1';
    code['F'] = '1';
    code['V'] = '1';

    code['C'] = '2';
    code['S'] = '2';
    code['K'] = '2';
    code['G'] = '2';
    code['J'] = '2';
    code['Q'] = '2';
    code['X'] = '2';
    code['Z'] = '2';

    code['D'] = '3';
    code['T'] = '3';
    code['L'] = '4';
    code['M'] = '5';
    code['N'] = '5';
    code['R'] = '6';

    char str[21] = {0};
    int n, m, c;
    int counter = 0;
    std::cout << std::setw(9) << " " << std::setw(25) << std::left << "NAME" << "SOUNDEX CODE" <<std::endl;
    while(scanf("%s\n", &str) != EOF)
    {
        counter++;
        out("In: %s\n", str);
        char ltr = str[0];
        std::string enc;
        enc.push_back(str[0]);
        char prev = code[str[0]];
        forl(i,1,strnlen(str,sizeof(str)-1)) {
            //if len already 3 break;
            if(enc.size() >= 4) break;
            char curr = code[str[i]];
            if(curr == prev)
                continue;

            prev = curr;
            if(curr == 0)
                continue;

            enc.push_back(curr);
        }
        while(enc.size() < 4) enc.push_back('0');

        //printf("          %10s %14s","NAME","SOUNDEX CODE");
        std::cout << std::setw(9) << " " << std::setw(25) << std::left << str << enc <<std::endl;
    }
    std::cout << "                   END OF OUTPUT"<<std::endl;

    return 0;
}
