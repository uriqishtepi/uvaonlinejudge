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

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

char matrix[500+1][500+1];

//get offset for x, y coordinates
inline int xyOff(int x, int y)
{
    return x*20000 + y; 
}

void printMat(int w, int h)
{
    forl(i,0,w+1) {
        forl(j,0,h+1)
            out("%d",matrix[i][j]);
        out("\n");
    }
}

void setWidth(int x, int y1, int y2, char val)
{
    static int count = 0;
    //out("set values from %d, + %d\n", xyOff(x,y1), y2 - y1 + 1);
    //memset(matrix + xyOff(x,y1), val, y2 - y1 + 1);
    //out("after memset\n");
    forl(i,y1,y2+1) {
        matrix[x][i]++;
    }
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    char * buff = NULL;
    int w, h, n;
    while( scanf("%d %d %d\n",&w,&h,&n) != EOF && w != 0) {
        out("%d %d %d\n",w,h,n);
        memset(matrix, 0, sizeof(matrix));

        forl(i,0,n) {
            int x1,y1,x2,y2;
            scanf("%d %d %d %d\n",&x1,&y1,&x2,&y2);
            out("Red %d %d %d %d\n",x1,y1,x2,y2);
            int xmin = std::min(x1,x2);
            int xmax = std::max(x1,x2);
            int ymin = std::min(y1,y2);
            int ymax = std::max(y1,y2);
            out("Act %d %d %d %d\n",xmin,ymin,xmax,ymax);
            forl(j,xmin,xmax+1) {
                out("set width %d %d %d\n",j,ymin,ymax);
                setWidth(j,ymin,ymax,1);
            }
        }

        int occup = 0;
        forl(i,1,w+1)
            forl(j,1,h+1)
                occup += (matrix[i][j] > 0);

        printMat(w+1,h+1);

        out("tot surface = %d, occup surface = %d\n",w*h,occup);
        int diff = w * h - occup;
        if(diff == 0)
            printf("There is no empty spots.\n");
        else if(diff == 1)
            printf("There is one empty spot.\n");
        else
            printf("There are %d empty spots.\n",diff);
    }
    return 0;
}

