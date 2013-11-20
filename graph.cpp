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

        int counter = 0;
        while(!q.empty())
        {
            int el = q.front();
            q.pop();
            if(visited[el])
                continue;

            printf("%d -> ", el);
            visited[el] = true;

            for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
            {
                if(!visited[*it])
                    q.push(*it);
            }
        }
    }
}


//follow node and print all adjacents
void DFS_follow(int node, const graphtp & g, vi &visited, std::string sofar)
{
    //follows all adjacent vertices of node
    for(vi::const_iterator it = g[node].begin(); it!=g[node].end();++it)
    {
        if(visited[*it])
            continue;
        
        std::cout << sofar << " -> " << *it;
        visited[*it] = true;
        
        DFS_follow(*it, g, visited, sofar + "      ");
        printf("\n");
    }
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
        visited[node] = true;
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

        int counter = 0;
        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            k.pop();

            if(visited[node])
                continue;

            printf("%d: %d \n", counter++, node);
            visited[node] = true;

            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(!visited[*it])
                    k.push(*it);
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

        int counter = 0;
        while(!q.empty())
        {
            int el = q.front();
            q.pop();
            if(visited[el])
                continue;

            printf("%d (%d)-> \n", el,compcntr);
            visited[el] = compcntr;

            for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
            {
                if(!visited[*it])
                    q.push(*it);
            }
        }
    }
}


//will print the nodes in the graph, starting with the one that does not point
//to any node first, then the others
//DFS print the one that has no neighbors
//note that if graph has cycles, there is no topological sort
void topological_sort(const graphtp &g)
{
    vi visited(g.size());
    int counter = 0;

    for(int n = 0; n < g.size(); n++)
    {
        if(visited[n])
            continue;

        std::stack<int> k;
        k.push(n);

        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            k.pop();

            if(visited[node])
                continue;

            printf("%d: %d \n", counter++, node);
            visited[node] = true;

            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(!visited[*it])
                    k.push(*it);
            }
        }
    }
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

    return 0;
}
