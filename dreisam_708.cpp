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

#define mis std::map<int, std::string>
#define vmis std::vector< mis > 

#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

#define DEBUG true
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

mis process_no_paren(std::string str)
{
    out("%s('%s')\n", __func__, str.c_str());
    mis ret;
    if(str.empty()) return ret;

    char * pstr = (char*) str.c_str();
    char *tok = strtok(pstr, " \n");

    if(tok == NULL) return ret;

    {
        int val = atoi(tok);
        out("normal addition %d\n", val);

        ret.insert(std::make_pair(val, tok));
    }

    while((tok = strtok(NULL, " \n") ) ) {
        int val = atoi(tok);
        addVal(ret, val, tok);
    }

    return ret;
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
mis process(std::string str)
{
    out("%s('%s')\n", __func__, str.c_str());
    //process chars one at a time, until we reach a ( 
    //in which case that's begin, look for closing ) that's end

    std::string::iterator br = std::find(str.begin(), str.end(), '(');

    if(br == str.end()) { 
        out("no paren was found");
        return process_no_paren(str);
    }
    assert(*br == '(');

    mis pre; 
    if(br != str.begin() && br - 1 != str.begin()) {
        pre = process_no_paren(std::string(str.begin(), br));
        out("pre size %d\n", pre.size());
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
    mis mid = process(std::string(br+1, ebr));
    out("mid size %d\n", mid.size());

    mis ret;
    ret = combine(pre, mid, true);
    out("ret size %d\n", mid.size());

    //process post
    if(ebr+1 != str.end()) {
        mis post = process(std::string(ebr+1, str.end()));
        ret = combine(ret, post, false);
    }
    return ret;

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
        mis zz = process(std::string(eqb+1, str.end()));

        /*
        while((str = strtok(NULL, "= \n") ) )
        {
            out("str %s\n",str);
            out("cur lvl %d\n",zz.size());
            if(str && str[0] == '(') {
                out("starts new subset\n");
                mis s;
                zz.push_back(s);

                int val = atoi(str+1);
                addVal(zz.back(), val, str+1);
            }
            else if(str && str[strlen(str) - 1] == ')') { 

                char cpy[80] = {0};
                strncpy(cpy, str, strlen(str) - 1);

                int val = atoi(cpy);
                out("closing parenth -- handle combinations %d\n", val);
                addVal(zz.back(), val, cpy);

                mis s = zz.back();
                zz.pop_back();
                if(zz.back().empty() ) {
                    for(mis::iterator it = s.begin(); it != s.end(); it++) {
                        zz.back().insert(make_pair(it->first, "("+it->second+")"));
                    }
                }
                else {
                    mis old = zz.back();
                    for(mis::iterator it = s.begin(); it != s.end(); it++) {
                        mis turn = old;
                        addVal(turn, it->first, "("+it->second+")");
                        for(mis::iterator jt = turn.begin(); jt != turn.end(); jt++) {
                            zz.back().insert(make_pair(jt->first,jt->second));
                        }
                    }
                }
            }
            else {
                int val = atoi(str);
                out("normal addition %d\n", val);
                addVal(zz.back(), val, str);
            }
        }
        */

        if(item > 1) printf("\n");
        printf("Equation #%d:\n",item);
        bool found = false;
        for(mis::iterator it = zz.begin(); it != zz.end(); it++) {
            out("considering %d %s\n", it->first, it->second.c_str());
            if(it->first == eq) {
                printf("%d=%s\n", eq, it->second.c_str());
                found = true;
                break;
            }
        }
        if(!found)
            printf("no solution\n");

        //printf("\n");
        free(buf);
    }
}

