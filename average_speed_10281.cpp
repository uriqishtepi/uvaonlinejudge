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

    char str[21] = {0};
    size_t n;
    int counter = 0;
    char * buff = NULL;
    float lastspeed = 0;
    float lasttime = 0;
    float lastdist = 0;

    while(getline(&buff, &n, stdin) > 0) 
    {
        int h, m, s, speed = -1;
        sscanf(buff, "%d:%d:%d %d",&h,&m,&s,&speed);
        out("%d:%d:%d %d\n",h,m,s,speed);
        char hs[30]={0};
        sscanf(buff, "%s ",&hs);
        if(speed < 0) {
            float loctime = h*3600+m*60+s;
            //dist will be lastdist + loctime*lastspeed
            printf("%s ", hs);
            printf("%.2f km\n", lastdist + (loctime-lasttime)*lastspeed);
        }
        else {
            float loctime = h*3600+m*60+s;
            lastdist += (loctime-lasttime)*lastspeed;

            lastspeed = (float)speed/3600;
            lasttime = loctime;
            out("New speedd\n");
        }
    }

    free(buff);
    return 0;
}
