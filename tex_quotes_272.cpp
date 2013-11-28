#include<stdio.h>
#include<math.h>
#include<iostream>
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

    char * buff = NULL;
    size_t n;
    bool first = true;
    while(getline(&buff, &n, stdin) > 0) {
        std::string line(buff);
        forl(i,0,strlen(buff)) {
            if(buff[i] == '"') {
                if(first) {
                    printf("``");
                    first = false;
                }
                else {
                    printf("''");
                    first = true;
                }
            }
            else 
                printf("%c",buff[i]);
        }
    }

    return 0;
}
