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

void DFS(const graphtp & g)
{
    out("DFS: size of g %d\n",g.size());
    vi visited(g.size());
    int counter = 0;

    for(graphtp::const_iterator it = g.begin(); it!=g.end();++it,++counter)
    {
        out("DFS element %d\n",counter);
        if(visited[counter])
            continue;
   
        printf("%d ", counter);
        visited[counter] = true;
        DFS_follow(counter, g, visited, "    ");
    }
}


void nonrecursive_DFS(const graphtp & g)
{
    vi visited(g.size());
    std::stack<int> k;
    int counter = 0;

    for(counter = g.size()-1; counter >= 0; counter--) 
    {
        k.push(counter);
    }

    counter = 0;
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


// connected components is effectivly DFS or BFS but assigns to visited for each
// element the id of its component; it assigns different ids
// for each distinct componnent
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

    std::cout << " DFS " << std::endl;
    nonrecursive_DFS(g);
    std::cout << std::endl;

    std::cout << " BFS " << std::endl;
    BFS(g);
    std::cout << std::endl;

    std::cout << " Connected Components " << std::endl;
    connected_components(g);
    std::cout << std::endl;

    return 0;
}
