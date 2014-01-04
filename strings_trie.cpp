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
