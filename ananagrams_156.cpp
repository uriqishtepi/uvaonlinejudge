/* find words that have no anagrams in the list */

#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<string.h>

#define  mypair  std::pair< std::string, int > 
#define  wmaptp  std::map<std::string, mypair > 
#define  vi      std::vector <std::string>

int main()
{
    char buff[81] = {0};
    int n;
    wmaptp wmap;

    while(fgets(buff, 80, stdin) != NULL) {
        char word[81];
        int offset = 0;
        int cnt = 0;
        while( sscanf(buff + offset, "%s%n", word, &cnt) != EOF) {
            if(strncmp(word, "#", 80) == 0) break;
            offset += cnt;
            std::string srtdword(word);
            std::transform(srtdword.begin(), srtdword.end(), 
                           srtdword.begin(), ::tolower);
            std::sort(srtdword.begin(), srtdword.end());
            wmaptp::iterator it = wmap.find(srtdword);
            if(it != wmap.end() ) {
                it->second.second++;
            }
            else { 
                wmap[srtdword] = std::make_pair(word, 1);
            }
            it = wmap.find(srtdword);
            //printf("srtedword: %s %s %d\n", it->first.c_str(), it->second.first.c_str(), it->second.second);
        }
    }
    vi finalsorted;
    for(wmaptp::iterator it = wmap.begin(); it != wmap.end(); it++) {
        if(it->second.second < 2)
            finalsorted.push_back(it->second.first);
    }
    std::sort(finalsorted.begin(), finalsorted.end());
    for(vi::iterator it = finalsorted.begin(); it != finalsorted.end(); it++)
        printf("%s\n", it->c_str());

    return 0;

}
