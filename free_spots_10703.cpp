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
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

struct fourpts {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct ltf {
    bool operator() (const fourpts & p1, const fourpts &p2)
    {
        if(p1.x1 != p2.x1)
            return p1.x1 < p2.x1;
        else if(p1.y1 != p2.y1)
            return p1.y1 < p2.y1;
        else if(p1.x2 != p2.x2)
            return p1.x2 < p2.x2;
        else
            return p1.y2 < p2.y2;
    }
};

int main(int argc, char **argv)
{
    out("Starting...\n");

    char * buff = NULL;
    int w, h, n;
    while( scanf("%d %d %d\n",&w,&h,&n) != EOF && w != 0) {
        out("%d %d %d\n",w,h,n);

        std::set <fourpts, ltf> v;
        forl(i,0,n) {
            int x1,y1,x2,y2;
            scanf("%d %d %d %d\n",&x1,&y1,&x2,&y2);
            out("%d %d %d %d\n",x1,y1,x2,y2);
            fourpts pt;
            pt.x1 = x1;
            pt.y1 = y1;
            pt.x2 = x2;
            pt.y2 = y2;
            v.insert(pt);
        }

        out("v size %d\n", v.size());
        std::set <fourpts, ltf> goodpts;
        goodpts.insert(*v.begin());
        //populate goodpts 

        for(std::set <fourpts, ltf>::iterator it = v.begin(); 
                it != v.end(); ++it) 
        {
            out("%d %d %d %d\n",it->x1,it->y1,it->x2,it->y2);
            //for jt in goodpoints
            //if *it intersects *jt then break up *it in several parts
            //and insert them in goodpts
        }

        int surface = 0;
        for(std::set <fourpts, ltf>::iterator it = v.begin(); 
                it != v.end(); ++it) 
        {
            surface += (1+it->x2 - it->x1) * (1+it->y2 - it->y1);
        }

        out("tot surface = %d, occup surface = %d\n",w*h,surface);
        int diff = w * h - surface;
        if(diff == 0)
            printf("There is no empty spots.\n");
        else if(diff == 1)
            printf("There is one empty spot.\n");
        else
            printf("There are %d empty spots.\n",diff);
    }
    return 0;
}

