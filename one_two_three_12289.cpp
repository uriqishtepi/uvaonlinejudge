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

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define vs std::vector<std::string>
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
    vs numbers;
    numbers.push_back("one");
    numbers.push_back("two");
    numbers.push_back("three");
    numbers.push_back("four");
    numbers.push_back("five");
    numbers.push_back("six");
    numbers.push_back("seven");
    numbers.push_back("eight");
    numbers.push_back("nine");
    numbers.push_back("ten");

    size_t n;
    std::cin >> n;
    out("n is %d\n", n);
    while(n-- > 0)
    {
        std::string word;
        std::cin >> word;
        out("word is %s\n", &word[0]);

        vs::iterator vit = numbers.begin();
        int numdiff = 0;
        for(; vit != numbers.end() && numdiff != 1; vit++) {
            numdiff = 0;
            if(word.length() != vit->length())
                continue;
            out("comparing with %s\n", &(*vit)[0]);
            for(int i = 0; i < word.length(); i++)
                numdiff += (word[i] != (*vit)[i]);
            out("numdiff is %d\n", numdiff);
            if(numdiff <= 1) {
                std::cout << vit - numbers.begin() + 1 << std::endl;
                break;
            }
        }
    }

    return 0;
}
