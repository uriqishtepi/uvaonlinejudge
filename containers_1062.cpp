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

a
bb
ccc


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
    std::set<char> uniq_chars;

    for(std::string::iterator it = word.begin(); it!=word.end(); ++it)
        uniq_chars.insert(*it);

    std::string::iterator it = word.begin(); 

    std::string order;
    order += *it;
    int smallest = 1;
out("0 inserting %c \n", *it);
    it++;
    while(it != word.end()) {

        char c = *it;
out("processing char %c\n", c);
out("order %s\n", order);

        std::string::iterator locit = find_if(order.begin(), order.end(), 
                std::bind2nd(std::greater_equal<char>(), c) );

        //int loc = find(order.begin(), order.end(), c, greater_equals(c));
        int loc = locit - order.begin();
out("found locit %c  >=  %c loc %d, order[loc] %c \n", *locit, c, loc, order[loc]);
        if(locit == order.end()) { /* not found, need to add to end */
            assert(order.size() < uniq_chars.size());
            order += c;
out("3 inserting %s\n", order);
        }
        else {
            assert(loc < order.size());
            assert(order[loc] >= c);
            order[loc] = c;
            std::sort(order.begin(), order.end());
        }

        if(order.size() >= uniq_chars.size()) break;
        it++;
    }

    std::cout << "Case  " << cases << ":  " << order.size() << std::endl;
}

int main()
{
    std::string word;
    int cases = 0;
    while(1) {
        std::cin >> word;
        if(word == "end")
            break;
        cases++;
        process_word(cases, word);
    }
}
