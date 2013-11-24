#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define vi std::vector<int>
#define graphtp std::vector< vi > 


//breadth first search
void BFS(const graphtp & g)
{
    vi visited(g.size());

    //consider all
    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        //start with current in queue
        std::queue<int> q;
        q.push(n);
        printf("\n");
        visited[n] = true;

        int counter = 0;
        while(!q.empty())
        {
            int el = q.front();
            q.pop();

            printf("%d -> ", el);

            for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
            {
                if(visited[*it]) 
                    continue;

                q.push(*it);
                visited[*it] = true;
            }
        }
    }
}

enum {white=0, gray=1, black=2,};


//follow node and print all adjacents
void DFS_follow(int node, const graphtp & g, vi &visited, std::string sofar)
{
    visited[node] = gray;
    //follows all adjacent vertices of node
    for(vi::const_iterator it = g[node].begin(); it!=g[node].end();++it)
    {
        if(visited[*it] == gray) {
            printf("cycle detected node %d\n", *it);
            continue;
        }        
        else if(visited[*it] == black) {
            out("visited node %d\n", *it);
            continue;
        }        

        std::cout << sofar << " -> " << *it;
        DFS_follow(*it, g, visited, sofar + "      ");
        printf("\n");
    }
    visited[node] = black;
}

void recursive_DFS(const graphtp & g)
{
    out("DFS: size of g %d\n",g.size());
    vi visited(g.size());

    for(int node=0; node < g.size(); node++)
    {
        out("DFS element %d\n",node);
        if(visited[node])
            continue;
   
        printf("%d ", node);
        DFS_follow(node, g, visited, "    ");
    }
}


void DFS(const graphtp & g)
{
    vi visited(g.size());

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        std::stack<int> k;
        k.push(n);
        visited[n] = true;

        int counter = 0;
        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            k.pop();

            printf("%d: %d \n", counter++, node);

            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(visited[*it]) {
                    out("visited node %d\n", *it);
                    continue;
                }
                k.push(*it);
                visited[*it] = true;
            }
        }
    }
}


// Find connected components for a undirected graph
// connected components is effectivly BFS but assigns to visited for each
// element the id of its component; it assigns different ids
// for each distinct componnent
// it works fine like this for a undirected graph because dfs (or bfs) 
// will find all the nodes in a component connected to the first node.
// however this does not work like so for directed graphs
// (does connected components make sense in directed graphs?)
void connected_components(const graphtp &g)
{
    vi visited(g.size());
    int compcntr = 0;

    //enque all
    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        std::queue<int> q;
        q.push(n);
        ++compcntr;
        visited[n] = compcntr;

        int counter = 0;
        while(!q.empty())
        {
            int el = q.front();
            q.pop();
            printf("%d (%d)-> \n", el,compcntr);

            for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
            {
                if(visited[*it]) {
                    out("visited node %d\n", *it);
                    continue;
                }

                q.push(*it);
                visited[*it] = compcntr;
            }
        }
    }
}


//topological sort of a directed acyclic graph is the reverse postorder of DFS
//postorder is the order items are popped from the stack
//
//will print the nodes in the graph, starting with the one that does not point
//to any node first, then the others
//DFS print the one that has no neighbors
//note that if graph has cycles, there is no topological sort
void topological_sort(const graphtp &g)
{
    vi visited(g.size());
    vi postorder; //order in which items are popped from stack
    int counter = 0;

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        vi locorder;
        std::stack<int> k;
        k.push(n);
        locorder.push_back(n);
        visited[n] = true;

        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            k.pop();

            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(visited[*it]) {
                    out("visited node %d\n", *it);
                    continue;
                }
                k.push(*it);
                locorder.push_back(*it);
                visited[*it] = true;
            }
        }
        postorder.insert(postorder.end(),locorder.rbegin(),locorder.rend());
    }

    printf("postorder: ");
    for(int n = 0; n < postorder.size(); n++)
        printf("%d ", postorder[n]);
    printf("\n");

    printf("reverse postorder: ");
    for(int n = postorder.size() - 1; n >= 0; n--)
        printf("%d ", postorder[n]);
    printf("\n");
    
}

void rec_topological_sort(const graphtp &g, vi & visited, vi & postorder, int node)
{
    visited[node] = true;
    for(vi::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
    {
        if(visited[*it])
            continue;
        rec_topological_sort(g, visited, postorder, *it);
    }
    postorder.push_back(node);
}


void recursive_topological_sort(const graphtp &g)
{
    vi visited(g.size());
    vi postorder;
    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;
        rec_topological_sort(g, visited, postorder, n);
    } 

    printf("postorder: ");
    for(int n = 0; n < postorder.size(); n++)
        printf("%d ", postorder[n]);
    printf("\n");

    printf("reverse postorder: ");
    for(int n = postorder.size() - 1; n >= 0; n--)
        printf("%d ", postorder[n]);
    printf("\n");
 
}




int main(void)
{
    out("starting ...\n");
    
    char * buff = NULL;
    graphtp g;
    size_t n;
    while( getline(&buff, &n, stdin) != -1 )
    {
        out("this is buff ='%s'\n", buff);
        char * tok = strtok(buff, " \n\t");
        out("this is node ='%s'\n", tok);
        if(tok == NULL) {
            printf("Error in input file");
            exit(1);
        }

        vi e;
        tok = strtok(NULL, " \n\t");
        while(tok > 0) 
        {
            out("red tok='%s'\n", tok);
            e.push_back(atoi(tok));
            tok = strtok(NULL, " \n\t");
        }
        g.push_back(e);
        out("size of g %d\n",g.size());
    }

    std::cout << " DFS " << std::endl;
    DFS(g);
    std::cout << std::endl;

    std::cout << " recursive DFS " << std::endl;
    recursive_DFS(g);
    std::cout << std::endl;

    std::cout << " BFS " << std::endl;
    BFS(g);
    std::cout << std::endl;

    std::cout << " Connected Components " << std::endl;
    connected_components(g);
    std::cout << std::endl;

    std::cout << " topogogical sort " << std::endl;
    topological_sort(g);
    std::cout << std::endl;

    std::cout << "Recursive DFS topogogical sort " << std::endl;
    recursive_topological_sort(g);
    std::cout << std::endl;

    return 0;
}
