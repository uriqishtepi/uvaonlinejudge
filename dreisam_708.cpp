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



int main(int argc, char **argv)
{
    out("Starting...\n");

    int s, rn; //s size, n number
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
        char *str = strtok(buf, "= ()\n");
        out("str %s\n",str);

        int eq = atoi(str);
        assert(eq >= 0);
        out("eq %d\n",eq);
        mis s;
        vmis zz;
        zz.push_back(s);

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

        s = zz.back();

        if(item > 1) printf("\n");
        printf("Equation #%d:\n",item);
        bool found = false;
        for(mis::iterator it = s.begin(); it != s.end(); it++) {
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

