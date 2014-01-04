/* rway trie
 * `simplest trie, have a vector of R items in each node
 * this is to be utitlized like a symbol table (map) so 
 * for each node there is a value and if falue is null or < 0 
 * then the node is not terminal, otherwise it is termninal
 * this wastes a lot of space and a better way is to compress
 * the 256 children to only as many as get used...and have the
 * first number to encode that amount.
 * other method is to use ternary tries (less eq gthen) 
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <queue>
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

int R = 256; //radix 2^8


inline
char charat(const std::string & s, int i)
{
    if(i < s.size()) return s.at(i);
    else return -1;
}

void insertion_sort(const std::vector<char *> & strings, std::vector<int> &v, int start, int end, int chrindx)
{
    for(int i = start; i < end - 1; i++){
        for(int j = i; j < end; j++) {
            if( strcmp(&strings[v[i]][chrindx], &strings[v[j]][chrindx]) > 0) {
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
            }
        }
    }

}



//pick a pivot, maybe randomly
//put all points above, less than and equal to in separate places of v[i]
void threeway_quicksort(const std::vector<char *> & strings, std::vector<int> &v, int start, int end, int chrindx)
{
    out("threeway_quicksort %d, %d, %d\n", start, end, chrindx);
    int n = end - start;
    if(n < 2) return;
    if(n < 20) { insertion_sort(strings, v, start, end, chrindx); return; }

    for(int i = start; i < end; i++) {
        out("h %s\n", strings[v[i]]);
    }

    //get the pivot
    int p = rand() % n;
    int c = charat(strings[v[start+p]],chrindx);
    out("p %d => c %c\n", start+p, c);

    int lessthan = start;
    int gtthan = end;
    int eqthan = 0;

    int i = start;
    while(i < gtthan) {
        int lc = charat(strings[v[i]],chrindx);
        out("i %d => lc %c\n", i, lc);
        if(lc < c)
        {
            int temp = v[lessthan];
            v[lessthan] = v[i];
            v[i] = temp;
            lessthan++;
            i++;
        }
        else if(lc > c)
        {
            gtthan--;
            int temp = v[gtthan];
            v[gtthan] = v[i];
            v[i] = temp;
        }
        else //equal
        {
            i++;
        }
    }

    out("lessthan %d\n", lessthan);
    out("gtthan %d\n", gtthan);
    out("gtthan - lessthan %d\n", gtthan - lessthan);

    for(int i = start; i < end; i++) {
        out("%d) strings[%d]=%s\n", i, v[i], strings[v[i]]);
    }

    threeway_quicksort(strings, v, start, lessthan, chrindx);
    threeway_quicksort(strings, v, lessthan, gtthan, chrindx + 1);
    threeway_quicksort(strings, v, gtthan, end, chrindx);
}

int binary_search(const std::vector<char *> & strings, std::vector<int> &v, char * str, int start, int end)
{
    out("binary_search %d, %d\n", start, end);
    if(end - start < 1) return -1;

    int mid = (start + end) / 2;
    int cmp = strcmp(strings[v[mid]], str);
    out("cmp %s, %s, %d\n", strings[v[mid]], str, mid);
    if(cmp < 0)
        return binary_search(strings, v, str, mid+1, end);
    else if(cmp > 0)
        return binary_search(strings, v, str, start, mid);
    else {
        return mid; //this is in fact a list of locations where the srch str appears
        //if we want all of them, we need to do a for loop forwards and backwards
        //to find them all
    }
}

int computesim(char*s1, char*s2)
{
    int len1 = strlen(s1);
    int i = 0;
    while(i < len1 && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return i;
}

//longest common substring
int lcs(const std::vector<char *> & strings, std::vector<int> &v)
{
    int maxlen = 0;
    int maxindex = 0;
    //search adjacent cells (after sortin) for the longest subsequence
    for(int i = 0; i < strings.size()-1; i++) {
        int llen = computesim(strings[v[i]],strings[v[i+1]]);
        if(maxlen < llen) {
            maxlen = llen;
            maxindex = i;
        }
    }

    printf("longes common substring is %s\n",strings[v[maxindex]]);
}

struct node {
    node() {
        memset(children, 0, sizeof(children));
        value = 0;
    }
    node*  children[256]; //if  n[i] exists, it means that a path goes through
    int value;    // some value associated with this node, if < 0 then not  terminal
};

void traverse_trie(node * root, std::string & str)
{
    if(!root) return;

    if(root->value)
        printf("%s %d\n",str.c_str(), root->value);

    //print accumulated string plus the char at this location
    for(int i = 0; i < R; i++) {
        if(root->children[i]) {
            str+=(char)i;
            traverse_trie(root->children[i], str);
            str.erase(str.end()-1);
        }
    }

}

int numItems = 0;

void insert_trie(node * root, char * str, int value)
{
    assert(root != NULL && "node passed in as root is null");
    assert(root->children != NULL && "node->children passed in as root is null");
    out("root %ld\n", &root);

    if(str == NULL || *str == '\0') {
        numItems++;
        root->value = value;
        return;
    }

    char c = str[0];

    if(root->children[c] == NULL)
    {
        root->children[c] = new node;
        out("new children[%d]=%ld\n", c, &root->children[c]);
    }
    insert_trie(root->children[c], str+1, value);
}


int main(void)
{
    out("starting ...\n");
    std::cout << " Strings R-trie " << std::endl;

    int N = 0;
    bool useallsubstrings = true; //to do a word search as you type

    node root; //trie root

    //start from 
    char str[256] = {0};
    int counterAsVal = 0;
    while( scanf("%s",&str) != EOF ) {
        out("root %ld\n", &root);
        int len = 1;
        if(useallsubstrings)
            len = strlen(str);

        for(int i = 0; i < len; i++) { 
            counterAsVal++;
            insert_trie(&root, i+str, counterAsVal);
        }
    }

    printf("traverse trie of size %d\n", numItems);
    std::string tmp;
    traverse_trie(&root, tmp); //prints only

    return 0;
}
