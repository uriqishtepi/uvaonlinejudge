#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include<list>
#include<assert.h>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<math.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define li std::list<int>
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
long long int count_occ(int n)
{
    long long int count = 1;
    while(n != 1) {
        out("n = %d\n",n);
        if(n & 0x1) {
            n += (n << 1) + 1;
        }
        else n = n >> 1;
        count++;
    }
    return count;
}

void printLoc(std::vector<int> &loc)
{
    forl(i, 0, loc.size()) {
        out("%d ",loc[i]);
    }
    out("\n");

}

void printListV(std::vector<li> &v)
{
    forl(i, 0, v.size()) {
        li &l = v[i];
        printf("%d:",i);
        for(li::iterator it = l.begin(); it!=l.end();++it) {
            printf(" %d", *it);
        }
        printf("\n");
    }
    out("\n");
}


//put all items after a to the original place
void putToOrig(std::vector<li> &v, std::vector<int> &loc, int a)
{
    out("a=%d is at loc[a]=%d\n",a,loc[a]);
    //take anything after a and move it to original position
    //need to find iterator for a
    li &l = v[loc[a]];
    li::iterator it = std::find(l.begin(), l.end(), a);
    assert(it != l.end());
    out("*it=%d\n",*it);
    //*it is element a

    li::iterator jt=l.end(); 
    jt--;
    while(*jt != *it) {
        //move *it to correct place
        out("*it=%d\n",*it);
        out("*jt=%d\n",*jt);
        loc[*jt] = *jt;
        l.splice(v[*jt].begin(), l, jt);
        jt=l.end(); 
        jt--;
    }
}


int main(int argc, char **argv)
{
    out("Starting...\n");

    char * buff = NULL;
    int count = 0;
    int m, n;
    out("count for %d = %d\n",22,count_occ(22));
    scanf("%d\n", &n);
    std::vector<li> v(n);
    std::vector<int> loc(n); //location of item i
    forl(i, 0, n) {
        v[i].push_back(i);
        loc[i] = i;
    }
    //printListV(v);
    printLoc(loc);

    char move[20];
    char over[20];
    int a, b;
    while(scanf("%s %d %s %d", &move, &a, &over, &b) != EOF)
    {
        if(loc[a] == loc[b])
            continue;

        if(strncmp(move, "move",4) ==0) {
            if(strncmp(over, "over",4) ==0) {
                //above a to orig, then move a
                putToOrig(v, loc, a);
            }
            else if(strncmp(over, "onto",4) ==0) {
                //above a and b to orig, then move a
                putToOrig(v, loc, a);
                putToOrig(v, loc, b);
            }
        }
        else if(strncmp(move, "pile",4) ==0) {
            if(strncmp(over, "onto",4) ==0) {
                //above b to orig, then move a 
                putToOrig(v, loc, b);
            }
            //else move a and all above it
        }
        //printListV(v);
        printLoc(loc);


        li &frmLst = v[loc[a]];
        li::iterator  fromIt = std::find(frmLst.begin(), frmLst.end(), a);
        out("looking for a=%d at loc %d\n", a, loc[a]);
        assert(fromIt != frmLst.end());

        li &toLst = v[loc[b]];
        li::iterator    toIt = std::find(toLst.begin(), toLst.end(), b);
        out("looking for b=%d at loc %d\n", b, loc[b]);
        assert(toIt != toLst.end());

        toIt = toLst.end();
        for(li::iterator jt = fromIt; jt != frmLst.end(); ++jt)
            loc[*jt] = loc[b];

        frmLst.splice(toIt, frmLst, fromIt, frmLst.end());

        //printListV(v);
        printLoc(loc);
    }
    printListV(v);
    return 0;
}

