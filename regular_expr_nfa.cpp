/* build the nfa machine corresponding to a regular expression
 * this is a bit heavy so the steps are to create one state (node) for
 * each letter in the regular expression, then to start connecting 
 * normal letters as next node, characters such as ( and ) denote 
 * beginning and ending of sequence, * '|' chooses either of 
 * two sub pieces, and '*' denotes repetition.
 *
 * Will use a graph to connect the epsilon transitions, can not 
 * use table because epsilon transitions can be more than one from
 * a given node (on * for instance need to go to two states).
 *
 * To be able to build the graph, we need to build separate subgraphs
 * for each alternate piece, and create empty connection 
 * from ( to character after |. 
 *
 * To be able to use the '*' we need to create three connections, 
 * one epsilon connection to the star itself, one epsilon connection to 
 * the begining of the sequence, and one to the next piece.
 *
 * When simulating the graph, you would need to start at each character 
 * in the text, so runtime would be M*N (M length of text, N length of pattern)
 *
 * When using this as a grep you would need to add (.* re .* ) so that 
 * it automatically looks for the pattern in each line of the input.
 * Added ability to perform check similar to grep, 
 * although it is not called by default, 
 * and also it does not color the output (which would require to
 * retreive the correct location of the regex).
 *
 */
#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


#define vi std::vector<int>
#define graphtp std::vector< vi > 

enum {white=0, gray=1, black=2,};


void print_graph(const graphtp & g)
{
    out("Printing Graph\n");
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
            out("%d, ", *it);
        }
        out("\n");
    }
}


/* one state per each character
 * go through the re and build the graph
 * if i-th is parethesis add epsilon edge from i to i+i
 * if 0-th is ( dont need to do anything special with edges
 * when we see a ( we push i into the stack
 * when we see a | or a ) we pop from the stack
 * and we link state of ( which we just popped, with state of ) or |
 *
 * modified so that it can take multiple | inside the same block
 */
void build_nfa_graph(graphtp & g, const char * re, int relen)
{
    for(int i = 0; i <= relen; i++)
        g.push_back(vi()); //initiate g connections with empty vectors

    std::stack<int> k;
    int last_previous = 0; //used to identify last ( or char for the link to *

    for(int i = 0; i < relen; i++)
    {
        //new epsilon trans from i to i+1 for ( and )
        if(re[i] == '(' || re[i] == ')') 
            g[i].push_back(i+1); //edge * to next state

        if(re[i] == '(' || re[i] == '|') { //push to stack symbol loc
            k.push(i);
        }

        if(re[i] == '*') { //three links when finding the * character
            g[i].push_back(i+1); //edge * to next state
            g[last_previous].push_back(i); //lastprev state to next state
            g[i].push_back(last_previous); //* to lastprev state
        }

        if(re[i] == ')')  //i is ) so need to pop from stack and process
        {
            int orloc = k.top();
            int next = i + 1;
            if(re[orloc] == '|') { //if poped symbol is | have work to do
                vi ors; //accumulate into ors all the | locations
                while(re[orloc] == '|') { //get all the | symbols in vector
                    ors.push_back(orloc);
                    k.pop();
                    orloc = k.top(); //set last previous to next in stack
                    last_previous = orloc; //set last previous to next in stack
                }

                //for all the | make two e-connections, one from ( and one to )
                for(vi::iterator it = ors.begin(); it != ors.end(); ++it) {
                    g[*it].push_back(i); //edge | to )
                    g[last_previous].push_back(*it + 1); //( to after |
                }
            }
            else last_previous = orloc; //else it is location of '('
            k.pop();
        }
        else last_previous = i;
    }

    print_graph(g);
}



/* depth first search, will mark the visited array as the result of the
 * search, start at node n and do dfs and mark visited for the reachable
 * states. 
 */
void dfs(const graphtp & g, int n, vi & visited)
{
    std::stack<int> k;
    k.push(n);

    int counter = 0;
    while(!k.empty()) 
    {
        //pop first
        int node = k.top();
        if(visited[node] == black) {
            k.pop();
            continue;
        }

        if(visited[node] != gray) {
            out("%d ", node);
        }
        out("%d: popped %d \n", counter++, node);
        visited[node] = gray;

        int anynew = 0;
        for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
        {
            if(visited[*it] == gray) {
                out("cycle detected node %d->%d\n", node, *it);
                continue;
            }        
            else if(visited[*it] == black) {
                out("encountered a prev. visited node %d\n", *it);
                continue;
            }
            k.push(*it);
            anynew++;
        }

        if(!anynew) {
            visited[node] = black;
            k.pop();
        }
    }
}



void print_visited(vi & visited)
{
    out("visited=");
    for(int i = 0; i != visited.size(); i++)
        out("%d, ", visited[i]);
    out("\n");
}


inline void get_visited(vi & visited, vi & states)
{
    states.resize(0);
    for(int i = 0; i != visited.size(); i++) {
        if(visited[i]) { 
            states.push_back(i);
            visited[i] = white;
        }
    }
}


/* check a text starting at 0 if it fulfills the regular expression
 * will search for the longest pattern that matches the RE
 * if at any moment we reach the final state, we store it in longestfound
 * but we continue to search so the we find indeed the longest txt
 * if it is successful will return the length of the match
 * if it in UNsucessful will return -1
 */
int check_nfa(const graphtp & g, const char * re, int relen, const char * text, int len, int & counter)
{
    out("check_nfa re='%s' text='%s'\n", re, text);
    int longestfound = -1;
    vi st;
    vi visited(relen+1);

    dfs(g, 0, visited); // get all possible states reachable from start state 0
    get_visited(visited, st);
    print_visited(visited);

    for(int i = 0; i < len && !st.empty(); i++) {
        for(vi::iterator it = st.begin(); it != st.end(); ++it) {
            int s = *it;
            if(s == relen) continue; //need to continue search tho

            if(text[i] == re[s] || re[s] == '.') {
                counter++;
                s = s + 1; //find ne state after it
                dfs(g, s, visited); //find all e-transitions from s
            }
        }

        if(visited.back()) longestfound = i;
        get_visited(visited, st);
        print_visited(visited);
    } 

    out("longestfound='%d'\n", longestfound);
    return longestfound;
}



int pattern_search(char * text, char * re)
{
    graphtp g;
    int len = strlen(text);
    int relen = strlen(re);
    build_nfa_graph(g, re, relen);
    int count = 0;
    int length = 0;
    int counter = 0;

    for(int i = 0; i < len; i++) {
        if((length=check_nfa(g, re, relen, text + i, len - i, counter)) >= 0) {
            count++;
            printf("found in location %d: %.*s (after %d probes)\n", i, length+1, text+i, counter);
        }
    }

    return count;
}

//grep version of the program
void grep(int argc, char **argv)
{
    std::cout << " Grep search argc "<< argc << std::endl;
    //argv[0] is the regual expression, argv[1] is the file to scan
    //if argc < 2 then we are dealing with standard input
    std::ifstream in; //TODO: = std::cin;
    if(argc < 2) {
        std::cerr << "Usage " << argv[0] << " <regex> [file] " << std::endl;
        exit(1);
    }
    if(argc > 2)
        in.open(argv[2], std::ifstream::in);

    std::string re = "(.*" + std::string(argv[1]) + ".*)"; //search for regex in the text
    int relen = re.size();
    graphtp g;
    build_nfa_graph(g, re.c_str(), relen);
    
    std::string text;
    int line = 0;
    while(in >> text)
    {
        int counter = 0;
        line++;
        int length = check_nfa(g, re.c_str(), relen, text.c_str(), text.size(), counter);
        if(length >= 0) {
            printf("found in line %d: %.*s (after %d probes)\n", line, length+1, text.c_str(), counter);
        }
    }
    
}

int main(int argc, char**argv)
{
    out("starting ... \n");
    //If you want grep, uncomment next line: 
    //grep(argc, argv); exit(1);
    
    std::cout << " Rexex search " << std::endl;

    char text[10000] = {0};
    char re[256] = {0};
    scanf("%s\n",&text);
    out("searching in %s \n", &text);
    while(scanf("%s\n",&re) != EOF) 
    { 
        int counter = 0;
        printf("searching for '%s' \n", re);
        int count = pattern_search(text, re);

        if(count > 0 ) printf("found in %d locations \n", count);
        else printf("NOT found in text\n");
    }

    return 0;
}

