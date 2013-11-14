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
#define mss std::map<std::string, std::string>
#define INF 1<<30;

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


int main(int argc, char **argv)
{
    out("Starting...\n");
    mss fmap;
fmap["A"]=".-";
fmap["J"]=".---";
fmap["S"]="...";
fmap["1"]=".----";
fmap["."]=".-.-.-";
fmap[":"]="---...";
fmap["B"]="-...";
fmap["K"]="-.-";
fmap["T"]="-";
fmap["2"]="..---";
fmap[","]="--..--";
fmap[";"]="-.-.-.";
fmap["C"]="-.-.";
fmap["L"]=".-..";
fmap["U"]="..-";
fmap["3"]="...--";
fmap["?"]="..--..";
fmap["="]="-...-";
fmap["D"]="-..";
fmap["M"]="--";
fmap["V"]="...-";
fmap["4"]="....-";
fmap["'"]=".----.";
fmap["+"]=".-.-.";
fmap["E"]=".";
fmap["N"]="-.";
fmap["W"]=".--";
fmap["5"]=".....";
fmap["!"]="-.-.--";
fmap["-"]="-....-";
fmap["F"]="..-.";
fmap["O"]="---";
fmap["X"]="-..-";
fmap["6"]="-....";
fmap["/"]="-..-.";
fmap["_"]="..--.-";
fmap["G"]="--.";
fmap["P"]=".--.";
fmap["Y"]="-.--";
fmap["7"]="--...";
fmap["("]="-.- -.";
fmap["\""]=".-..-.";
fmap["H"]="....";
fmap["Q"]="--.-";
fmap["Z"]="--..";
fmap["8"]="---..";
fmap[")"]="-.--.-";
fmap["@"]=".--.-.";
fmap["I"]="..";
fmap["R"]=".-.";
fmap["0"]="-----";
fmap["9"]="----.";
fmap["&"]=".-...";

    mss revmap;
    for(mss::iterator it = fmap.begin(); it != fmap.end(); ++it)
        revmap[it->second]= it->first;

    char * buff = NULL;
    int count = 0;
    int m;
    scanf("%d\n", &m); //number of items
    size_t n;

    while( getline(&buff, &n, stdin) != -1)
    {
        std::string msg;
        int len = 0;
        char * tok = strtok(buff, " \n");
        while(tok) {
            out("%s\n",tok);
            mss::iterator it;
            len += strlen(tok);
            out("len = %d, buff len = '%c', buff=%s\n", len, buff[len], buff);
            if(buff[len] == ' ') {
                msg += " ";
                len += 1;
            }

            if((it = revmap.find(tok)) != revmap.end())
                msg += it->second;
            else
                out("token %s not found\n",tok);

            tok = strtok(NULL, " \n");
        }
        std::cout << "Message " << ++count << std::endl;
        std::cout << msg << std::endl << std::endl;
    }
    return 0;
}

