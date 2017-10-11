/* 
one configuration is a set of piles storing the last element, represented as a sorted string    "abc"
store all combinations if different in a set to avoid dups


given initial empty combination, combinations.insert(string(c))

for comb in combinations
  if(comb contains c)
     done (we put at the top of comb)
  put c on top of each existing position sort word and insert that as a new comb
  appended c at the end of comb, sort word, and insert in comb if len < numchars we have seen so far

cbacbacbacba

c b a
c b a
c b a
c b a

aaaa
bbbb
cccc


z
g
cgz

g
cz

cgz gzgzgzgzgz

*/

#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <assert.h>

#ifdef DEBUG
#define out printf
#else 
void out(...) {}
#endif

struct greater_equals : public std::unary_function<bool, char> {
    char _c;
    greater_equals(char c) { _c=c;}
    bool operator()(char a) { return a >= _c; }
};

#define ss std::set<std::string> 

void process_word(int cases, std::string word)
{
    ss combinations;
    std::set<char> uniq_chars;

    for(std::string::iterator it = word.begin(); it!=word.end(); ++it)
        uniq_chars.insert(*it);

    std::string::iterator it = word.begin(); 
    std::string tmp;
    tmp += *it;
    combinations.insert(tmp);
    int smallest = 1;
out("0 inserting %c \n", tmp);
    it++;
    while(it!=word.end()) {
        smallest = 27;

        char c = *it;
out("processing char %c\n", c);
        ss new_combinations;

        for(ss::iterator sit = combinations.begin(); sit != combinations.end(); sit++) {
            std::string curr_str = *sit;
out("processing curr_str %s\n", curr_str);
            std::string::iterator locit = find_if(curr_str.begin(), curr_str.end(), std::bind2nd(std::greater_equal<char>(), c) );
            //int loc = find(curr_str.begin(), curr_str.end(), c, greater_equals(c));
            int loc = locit - curr_str.begin();
out("found locit %c  >=  %c loc %d, curr_str[loc] %c \n", *locit, c, loc, curr_str[loc]);
            if(locit == curr_str.end()) {
out("goto append \n");
                goto append;
            }

            assert(curr_str[loc] >= c);
            if(curr_str[loc] == c) {
out("1 inserting %s\n", curr_str);
                new_combinations.insert(curr_str);
                if(curr_str.size() < smallest) smallest = curr_str.size();
                continue;
            }
            for(; loc < curr_str.size(); loc++) {
                std::string copy = curr_str;
                copy[loc] = c;
                std::sort(copy.begin(), copy.end());
out("2 inserting %s\n", copy);
                new_combinations.insert(copy);
                if(copy.size() < smallest) smallest = copy.size();
            }
append:
            if(curr_str.size() < uniq_chars.size()) {
                curr_str += c;
out("3 inserting %s\n", curr_str);
                new_combinations.insert(curr_str);
                if(curr_str.size() < smallest) smallest = curr_str.size();
            }
        }
        if(smallest >= 26) break;
        combinations = new_combinations;
        it++;
    }

    std::cout << "Case  " << cases << ":  " << smallest << std::endl;
}

int main()
{
    std::string word;
    int cases;
    while(1) {
        std::cin >> word;
        if(word == "end")
            break;
        cases++;
        process_word(cases, word);
    }
}
