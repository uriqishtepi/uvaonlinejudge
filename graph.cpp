#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
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

void print_graph(const graphtp & g)
{
    for(int n = 0; n < g.size(); n++)
    {
        out("%d: ", n);
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it)
        {
            out("%d, ", *it);
        }
        out("\n");

    }

}

//breadth first search
//expand the reach from a node, level at at time
//extremely hard to find cycles with bfs
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
//first time we encounter node, we mark it gray
//then we process all its dfs connected subtree
//when we are done, we mark it black
//if during the dfs search we see node that is gray, it means we have cycle
//if we encounter black node, it means it was independently fully processed
//earlier and nothing further should be done with it
void DFS_follow(int node, const graphtp & g, vi &visited, std::string sofar)
{
    visited[node] = gray;
    //follows all adjacent vertices of node
    for(vi::const_iterator it = g[node].begin(); it!=g[node].end();++it)
    {
        if(visited[*it] == gray) {
            printf("cycle detected node %d->%d\n", node, *it);
            continue;
        }        
        else if(visited[*it] == black) {
            out("encountered a prev. visited node %d\n", *it);
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
                    out("encountered a prev. visited node %d\n", *it);
                    continue;
                }
                k.push(*it);
                visited[*it] = true;
            }
        }
    }
}


void DFS_that_detects_cycles(const graphtp & g)
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
            if(visited[node] == black) {
                k.pop();
                continue;
            }
            visited[node] = gray;

            printf("%d: %d \n", counter++, node);

            int anynew = 0;
            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(visited[*it] == gray) {
                    printf("cycle detected node %d->%d\n", node, *it);
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
                    out("encountered a prev. visited node %d\n", *it);
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

    for(int n = 0; n < g.size(); n++) //go through all the nodes in the graph
    {
        if(visited[n]) //nothing more to do with this node
            continue;

        std::stack<int> k;
        k.push(n);

        while(!k.empty()) 
        {
            //pop first
            int node = k.top();
            if(visited[node] == black) { //node can be put in stack mult times
                k.pop();
                continue;
            }

            visited[node] = gray;

            int anynew = 0;
            for(vi::const_reverse_iterator it = g[node].rbegin(); it != g[node].rend(); ++it)
            {
                if(visited[*it] == gray) {
                    printf("cycle detected node %d->%d\n", node, *it);
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
                k.pop();
                visited[node] = black;
                postorder.push_back(node);
            }
        }
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
    visited[node] = gray;
    for(vi::const_iterator it = g[node].begin(); it != g[node].end(); ++it)
    {
        if(visited[*it] == gray) {
            printf("cycle detected node %d->%d\n", node, *it);
            continue;
        }        
        else if(visited[*it] == black) {
            out("encountered a prev. visited node %d\n", *it);
            continue;
        }
        rec_topological_sort(g, visited, postorder, *it);
    }
    visited[node] = black;
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

//compute the reverse graph
void get_reverse_graph(const graphtp &g, graphtp &rev)
{
    rev.resize(g.size());
    for(int n = 0; n < g.size(); n++)
    {
        for(vi::const_iterator it = g[n].begin(); it != g[n].end(); ++it)
        {
            rev[*it].push_back(n);
        }
    }
}


//alternative topological sort based on finding nodes that have no incomming
//(or out going) edges, then expanding with the nearest neighbors and so on
//until all the vertices are proessed. there must be at least one vertex with 
//no incommint edge, otherwise there would be a cycle and no topol sort.
//After finding nodes with no connectionns outside, do a sort of BFS on graph
//except that add node with only connections to the visited nodes 
//This is a bit similar to MST (min spanning tree)
//We might need to reverse thd edges to find equivalent order to the 
//DFS based topological sort above
void alt_topol_sort(const graphtp &g)
{
    std::queue<int> q;
    //need the reverse graph:
    graphtp rev;
    get_reverse_graph(g, rev);
    print_graph(rev);

    //find vertices with no incomming (outgoing?) edges
    for(int n = 0; n < rev.size(); n++)
    {
        if(rev[n].size() == 0)
            q.push(n);
    } 

    vi visited(g.size());

    while(!q.empty())
    {
        int el = q.front();
        q.pop();
        if(visited[el]) //avoid processing items that were put in q mult times
            continue;

        printf("%d ", el);
        visited[el] = true;

        for(vi::const_iterator it = g[el].begin(); it != g[el].end(); ++it)
        {
            out("\nneighbors of %d investigating node %d\n",el, *it);

            if(visited[*it]) {
                out("already visited %d\n", *it);
                continue;
            }

            bool feasable = true;
            for(vi::const_iterator jt = rev[*it].begin(); jt!= rev[*it].end();
                    ++jt) 
            {
                out("\nnode %d depends on %d\n",*it, *jt);
                if(!visited[*jt]) {
                    out("\n %d is not visited yet\n", *jt);
                    feasable = false;
                    break;
                }
            }

            if(!feasable)
                continue;

            q.push(*it); 
            //can not mark visited here otherwise the rev check will fail
            //so have to mark visited when popping--this introduces possibility
            //of a node going multiple times on the que
            //we can avoid it by marking gray when put in queue
            //and marking black when popping out from queue.
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


    print_graph(g);

    std::cout << " DFS " << std::endl;
    DFS(g);
    std::cout << std::endl;

    std::cout << " DFS with cycle detection " << std::endl;
    DFS_that_detects_cycles(g);
    std::cout << std::endl;


    std::cout << " recursive DFS " << std::endl;
    recursive_DFS(g);
    std::cout << std::endl;

    std::cout << "BFS " << std::endl;
    BFS(g);
    std::cout << std::endl;

    std::cout << "Connected Components " << std::endl;
    connected_components(g);
    std::cout << std::endl;

    std::cout << "topogogical sort " << std::endl;
    topological_sort(g);
    std::cout << std::endl;

    std::cout << "topogogical sort via Recursive DFS " << std::endl;
    recursive_topological_sort(g);
    std::cout << std::endl;

    std::cout << "topogogical sort via BFS on reverse graph" << std::endl;
    alt_topol_sort(g);
    std::cout << std::endl;

    return 0;
}
