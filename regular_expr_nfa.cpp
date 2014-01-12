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
 */
#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>
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


//one state per each character
//go through the re and build the graph
//if i-th is parethesis add epsilon edge from i to i+i
//if 0-th is ( dont need to do anything special with edges
//when we see a ( we push i into the stack
//when we see a | or a ) we pop from the stack
//and we link state of ( which we just popped, with state of ) or |
void build_nfa_graph(graphtp & g, char * re, int relen)
{
    for(int i = 0; i <= relen; i++)
        g.push_back(vi());


    std::stack<int> k;
    int last_previous = 0; //used to identify last ( or last |

    for(int i = 0; i < relen; i++)
    {
        //last character or last paren to return to in case of a * 

        //new epsilon trans from i to i+1 for (, ), and *
        if(re[i] == '(' || re[i] == ')' || re[i] == '*') 
            g[i].push_back(i+1); //* to next state

        if(re[i] == '(' || re[i] == '|') { //push to stack symbol loc
            k.push(i);
        }

        if(re[i] == '*') {
            g[last_previous].push_back(i); //lastprev state to next state
            g[i].push_back(last_previous); //* to lastprev state
        }

        if(re[i] == ')') { //i is ) so need to pop and process
            int orloc = k.top();
            int next = i + 1;
            if(re[orloc] == '|') { //get symbol, if | have work to do
                g[orloc].push_back(i); //| to )
                k.pop();
                last_previous = k.top(); //mark ( as last previous
                g[last_previous].push_back(orloc+1); //( to after |
            }
            else last_previous = orloc;
            k.pop();
        }
        else last_previous = i;

    }

    print_graph(g);
}



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



//check a text starting at 0 if it fulfills the regular expression
//will search for the longest pattern that matches the RE
//if it is successful will return the length of the match
//if it in UNsucessful will return -1
int check_nfa(const graphtp & g, char * re, int relen, char * text, int len)
{
    out("check_nfa re='%s' text='%s'\n", re, text);
    int longestfound = -1;
    //get all the possible states reachable from start state 0
    vi st;
    vi visited(relen+1);
    dfs(g, 0, visited); 
    for(int i = 0; i != visited.size(); i++)
        if(visited[i]) { 
            st.push_back(i);
            visited[i] = white;
        }

    print_visited(visited);

    for(int i = 0; i < len && !st.empty(); i++) 
    {
        //if at any moment we reach the final state, we return true

        for(vi::iterator it = st.begin(); it != st.end(); ++it)
        {
            int s = *it;
            if(s == relen) continue; //need to continue search tho

            if(text[i] == re[s] || re[s] == '.') {
                s = s + 1; //find ne state after it
                dfs(g, s, visited); //find all e-transitions from s
            }
        }

        print_visited(visited);

        if(visited.back()) longestfound = i;

        st.resize(0);
        for(int i = 0; i != visited.size(); i++)
            if(visited[i]) { 
                st.push_back(i);
                visited[i] = white;
            }
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

    for(int i = 0; i < len; i++) {
        if((length=check_nfa(g, re, relen, text + i, len - i)) >= 0) {
            count++;
            printf("found in location %d: %.*s \n", i, length+1, text+i);
        }
    }

    return count;
}



int main(int argc, char**argv)
{
    out("starting ...\n");
    std::cout << " Rexex search " << std::endl;

    char text[10000] = {0};
    char re[256] = {0};
    scanf("%s\n",&text);
    out("searching in %s \n", &text);
    while(scanf("%s\n",&re) != EOF) 
    { 
        int counter = 0;
        int count = pattern_search(text, re);

        if(count > 0 ) printf("found in %d locations \n", count);
        else printf("NOT found in text\n");
    }

    return 0;
}

