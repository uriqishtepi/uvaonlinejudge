/* ternary trie
 * this method of having a trie, makes better use of memory
 * each node will have three children, lessthan, equal, gtthan
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
    node() : lessthan(NULL) ,equal(NULL) ,gtthan(NULL) ,value(0) ,c(' ')
    {
    }
    node *lessthan; //if  n[i] exists, it means that a path goes through
    node *equal; //if  n[i] exists, it means that a path goes through
    node *gtthan; //if  n[i] exists, it means that a path goes through
    int  value;    // some value associated with this node, if < 0 then not  terminal
    char c;
};

void traverse_trie(node * root, std::string & str)
{
    if(!root) return;

    if(root->value) {
        printf("%s %d\n",str.c_str(), root->value);
    }

    if(root->lessthan) {
        traverse_trie(root->lessthan, str);
    }    

    //print accumulated string plus the char at this location
    if(root->equal) {
        str += root->c;
        traverse_trie(root->equal, str);
        str.erase(str.end()-1);
    }

    if(root->gtthan) {
        traverse_trie(root->gtthan, str);
    }
}

int numItems = 0;

void insert_trie(node * root, char * str, int value)
{
    assert(root != NULL && "node passed in as root is null");
    out("root %ld\n", &root);

    if(str == NULL || *str == '\0') {
        numItems++;
        root->value = value;
        return;
    }

    char c = str[0];

    if(root->equal == NULL)
    {
        root->equal = new node;
        root->c = c;
        out("new children[%d]=%ld\n", c, &root->equal);
        insert_trie(root->equal, str+1, value);
        return;
    }    

    if(c < root->c)
    {
        if(root->lessthan == NULL) {
            root->lessthan = new node;
            root->lessthan->c = c;
            out("new children[%d]=%ld\n", c, &root->equal);
        }
        insert_trie(root->lessthan, str, value);
    }    
    else if(c > root->c)
    {
        if(root->gtthan == NULL) {
            root->gtthan = new node;
            root->gtthan->c = c;
            out("new children[%d]=%ld\n", c, &root->equal);
        }
        insert_trie(root->gtthan, str, value);
    }
    else
        insert_trie(root->equal, str+1, value);
}


int main(void)
{
    out("starting ...\n");
    std::cout << " Strings ternary-trie " << std::endl;

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
