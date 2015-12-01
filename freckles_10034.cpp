/* connect dots to minimize ink
 * this is an mst problem
 */
#include<map>
#include<stdio.h>
#include<math.h>
#include<assert.h>
#define MAX 100
#define pi std::pair<int, int>
#define mi std::multimap<float, pi >

float mst(float arr[][2], float D[][MAX+1], int n)
{
    //start from any point, will connect to the nearest only
    //need a priority queue here
    mi q;
    bool visited[MAX+1] = {0};
    for(int i = 1; i < n; i++)
        q.insert(std::make_pair(D[0][i] , std::make_pair(0,i)));
    visited[0] = 1;
    float tot = 0;
    while(! q.empty() )
    {
        pi p = q.begin()->second;
        float d = sqrt(q.begin()->first);
        q.erase(q.begin());

        int curr = p.second;
        if(visited[curr]) continue;

        tot += d;
        printf("getting link %d-%d with d=%f\n", p.first, p.second, d);
        visited[curr] = 1;
        for(int i = 1; i < n; i++) {
            if(!visited[i])
                q.insert(std::make_pair(D[curr][i] , std::make_pair(curr,i)));
        }
    }
    return tot;
}

int main() 
{
    int cases;
    scanf("%d", &cases);
    while(cases-- > 0) {
        float arr[MAX+1][2] = {{0}};
        float D[MAX+1][MAX+1] = {{0}};
        int n;
        scanf("%d", &n);
        assert(n > 0 && n <= MAX);
        int i;
        while(i < n) {
            scanf("%f %f", &arr[i][0], &arr[i][1]);
            int j;
            for(j=0;j<i;j++) {
                float dx = arr[i][0] - arr[j][0];
                float dy = arr[i][1] - arr[j][1];
                float d = dx*dx + dy*dy;
                D[j][i] = d;
                D[i][j] = d;
            }

            i++;
        }
        printf("%.2f\n", mst(arr, D, n));
    }
    return 1;
}
