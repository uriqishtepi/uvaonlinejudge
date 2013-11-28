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

    char *line = NULL;
    size_t n;
    while(getline(&line, &n, stdin) >= 0) 
    {
        std::istringstream ss (line);
        std::string sg;
        ss >> sg;
        while(!ss.eof()) {
            reverse(sg.begin(), sg.end());
            std::string next;
            ss >> next;
            if(ss.eof())
                std::cout << sg;
            else
                std::cout << sg << " ";

            sg = next;
        }

        std::cout << std::endl;
    }

    free(line);
    return 0;
}
