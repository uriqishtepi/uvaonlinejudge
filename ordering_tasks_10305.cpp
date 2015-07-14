#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <assert.h>
#include <stdio.h>

#define graph std::map<int, std::vector <int> >
#define links std::vector<int>

//this is also known as topological sort
//dfs on an entry, when terminal node, print and do dfs on the reverse graph


//2 4
//2 5
//1 7
//1 2

#define MAXNODES 100
#define INSTACK 1
#define DONE 2

links afters[MAXNODES+1];
links befores[MAXNODES+1];
bool firstinline;

void DFS(int node, int visited[])
{
    //printf("DFS %d\n", node);
    if(visited[node] == 2) return;

    std::stack<int> st;
    st.push(node);
    visited[node] = INSTACK;

    while(!st.empty()) {
        int curr = st.top();
        st.pop();
        if(visited[curr] == DONE) continue;
        assert(visited[curr] == INSTACK);

        if(befores[curr].empty()) { //nothing before this node
            printf("%s%d", (firstinline ? "" : " "), curr);
            firstinline = false;
            visited[curr] = DONE;
        }
        else {
            int count = 0;
            for(links::iterator it = befores[curr].begin(); it != befores[curr].end(); ++it) 
                if(!visited[*it]) count++;

            if(count > 0) { 
                st.push(curr); //put it back to process later
            }
            else {
                printf("%s%d", (firstinline ? "" : " "), curr);
                firstinline = false;
                visited[curr] = DONE;
            }

            for(links::iterator it = befores[curr].begin(); it != befores[curr].end(); ++it) {
                //printf("Looking at %d which is before of %d\n", *it, curr);
                if(visited[*it]) continue;
                count++;
                visited[*it] = INSTACK;
                st.push(*it);
                //printf("Pusshing %d which is before of %d\n", *it, curr);
            }

        }
    }

    /*
    for(links::iterator jt = afters[curr].begin(); jt != afters[curr].end(); ++jt) {
        int prv  = *jt;
        visited[prv] = INSTACK;
        sk.push(prv);
    }
    */
}


int main() 
{
    int m, n;
    while(scanf("%d %d" , &n, &m) != EOF && !(m == 0 && n == 0)) {
        assert( n >= 1 && n <= MAXNODES);
        int i;
        for(i=0;i<n;i++) {
            befores[i].resize(0);
            afters[i].resize(0);
        }
        for(i=0;i<m;i++) {
            int one, two;
            scanf("%d %d", &one, &two); //two must be after one: from one to two
            befores[two].push_back(one);//before two is one
            afters[one].push_back(two); //after one is two
        }

        int visited[100] = {0};
        firstinline = true;
        int j = 1;
        while (j <= n) {
            assert(visited[j] != INSTACK);
            if(visited[j] == DONE) continue;
            //findend 
            DFS(j, visited);
            j++;
        }
        printf("\n");
    }
    return 0;
}
