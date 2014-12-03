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
#include <assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define vd std::vector<double>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define vsi std::vector< std::set <int> > 

#define mis std::map<long long int, std::string>
#define vmis std::vector< mis > 

#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


void addVal(mis & s, int val, std::string str)
{
    out("%s(,%d,%s)\n", __func__, val, str.c_str());
    if(s.empty()) {
        s.insert(std::make_pair(val, str));
        return;
    }

    mis ns;
    for(mis::iterator it = s.begin(); it != s.end(); it++) {
        out("forl adding to %d:%s %d:%s\n", it->first, it->second.c_str(),
               it->first + val, (it->second + "+" + str).c_str());
        out("forl adding to %d:%s %d:%s\n", it->first, it->second.c_str(),
               it->first - val, (it->second + "-" + str).c_str());
        out("forl adding to %d:%s %d:%s\n", it->first, it->second.c_str(),
               it->first * val, (it->second + "*" + str).c_str());
        ns.insert(std::make_pair(it->first + val, it->second + "+" + str));
        ns.insert(std::make_pair(it->first - val, it->second + "-" + str));
        ns.insert(std::make_pair(it->first * val, it->second + "*" + str));
    }
    s = ns;
}

void process_no_paren(mis & ret, std::string str)
{
    out("%s('%s')\n", __func__, str.c_str());
    if(str.empty()) return;

    char * pstr = (char*) str.c_str();
    char *tok = strtok(pstr, " \n");

    if(tok == NULL) return;

    {
        int val = atoi(tok);
        out("normal addition %d\n", val);

        addVal(ret, val, tok);
    }

    while((tok = strtok(NULL, " \n") ) ) {
        int val = atoi(tok);
        addVal(ret, val, tok);
    }
}

mis combine(mis & first, mis & second, bool haspar)
{
    out("%s()\n", __func__);
    mis ret;
    if(first.size() > 0 && second.size() > 0) {
        for(mis::iterator it = second.begin(); it != second.end(); it++) {
            out("%s : %d:%s\n", __func__, it->first, it->second.c_str());
            mis turn = first;
            if(haspar)
                addVal(turn, it->first, "("+it->second+")");
            else
                addVal(turn, it->first, it->second);
            //append to ret
            for(mis::iterator jt = turn.begin(); jt != turn.end(); jt++) {
                ret.insert(make_pair(jt->first,jt->second));
            }
        }
    }
    else if(first.size() > 0)
        ret = first;
    else if (second.size() > 0 && haspar) {
        for(mis::iterator jt = second.begin(); jt != second.end(); jt++) {
            ret.insert(make_pair(jt->first, "("+jt->second+")"));
        }
    }
    else if(second.size() > 0)
        ret = second;
    else abort();

    return ret;
}


//process a string like 7 3
//or 1 (3 4) 3
//or ((1 2))
void process(mis & ret, std::string str)
{
    out("%s('%s')\n", __func__, str.c_str());
    //process chars one at a time, until we reach a ( 
    //in which case that's begin, look for closing ) that's end

    std::string::iterator br = std::find(str.begin(), str.end(), '(');

    if(br == str.end()) { 
        out("no paren was found");
        process_no_paren(ret, str);
        return;
    }
    assert(*br == '(');

    if(br != str.begin() && br - 1 != str.begin()) {
        process_no_paren(ret, std::string(str.begin(), br));
        out("ret size %d\n", ret.size());
    }

    //process part with paren
    std::string::iterator ebr = br;
    int bcount = 1;
    while((++ebr) != str.end()) {
        if(*ebr == ')') bcount --;   
        else if(*ebr == '(') bcount ++;   
        assert(bcount >= 0);
        if(bcount == 0)
            break;
    }
    assert(ebr != str.end() && "must find closing paren");
    assert(*ebr == ')');
    mis mid;
    process(mid, std::string(br+1, ebr));
    out("mid size %d\n", mid.size());

    ret = combine(ret, mid, true);
    out("ret size %d\n", mid.size());

    //process post
    if(ebr+1 != str.end()) {
        process(ret, std::string(ebr+1, str.end()));
    }
}


int main(int argc, char **argv)
{
    out("Starting...\n");

    int item = 0;
    while(1) 
    {
        item++;
        size_t n;
        char *buf = NULL;
        if(getline(&buf, &n, stdin) == -1)
            return 0;
        if(buf[0] == '0')
            return 0;

        out("line: %s\n", buf);

        int eq = 0;
        sscanf(buf, "%d", &eq);

        assert(eq >= 0);
        out("eq %d\n",eq);
        std::string str = std::string(buf);
        std::string::iterator eqb = std::find(str.begin(),str.end(),'=');
        assert(eqb != str.end());
        mis zz;
        process(zz, std::string(eqb+1, str.end()));

        printf("Equation #%d:\n",item);
        
        mis::iterator it = zz.find(eq); 
        if(it != zz.end()) {
            out("found %d %s\n", it->first, it->second.c_str());
            printf("%d=%s\n", eq, it->second.c_str());
        }
        else printf("Impossible.\n");

        printf("\n");
        free(buf);
    }
}

