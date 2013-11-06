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
    unsigned char code[26] = {0};
    code['I'] = 0;
    code['U'] = 0;
    code['A'] = 0;
    code['E'] = 0;
    code['O'] = 0;
    code['Y'] = 0;
    code['W'] = 0;
    code['H'] = 0;
    code['B'-'A'] = 1;
    code['P'-'A'] = 1;
    code['F'-'A'] = 1;
    code['V'-'A'] = 1;
    code['S'-'A'] = 2;
    code['K'-'A'] = 2;
    code['G'-'A'] = 2;
    code['J'-'A'] = 2;
    code['Q'-'A'] = 2;
    code['X'-'A'] = 2;
    code['Z'-'A'] = 2;
    code['D'-'A'] = 3;
    code['T'-'A'] = 3;
    code['L'-'A'] = 4;
    code['M'-'A'] = 5;
    code['N'-'A'] = 5;
    code['R'-'A'] = 6;

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
        char prev = code[str[0]-'A'];
        forl(i,1,strnlen(str,sizeof(str)-1)) {
            //if len already 3 break;
            if(enc.size() >= 4) break;
            char curr = code[str[i] - 'A'];
            if(curr == 0 || curr == prev) { 
                prev = curr;
                continue;
            }

            enc.push_back(curr+'0');
            prev = curr;
        }
        while(enc.size() < 4) enc.push_back('0');

        //printf("          %10s %14s","NAME","SOUNDEX CODE");
        std::cout << std::setw(9) << " " << std::setw(25) << std::left << str << enc <<std::endl;
    }
    std::cout << "                   END OF OUTPUT"<<std::endl;

    return 0;
}
