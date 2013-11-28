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
    unsigned char code[][50] = { " 1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./ ", " `1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./"};

    char str[21] = {0};
    size_t n;
    int counter = 0;
    char * buff = NULL;
    out("sizeof sizeof(code[0]) %d\n",sizeof(code[0]));
    while(getline(&buff, &n, stdin) > 0) 
    {
        forl(i,0,strlen(buff)) {
            int indx = -1;

            forl(j,0,sizeof(code[0])) {
                if(code[0][j] == buff[i]) {
                    indx = j;
                    break;
                }
            }
            if(indx >= 0 && indx < sizeof(code[0])) 
                printf("%c", code[1][indx]);
        }
        printf("\n");

    }

    return 0;
}
