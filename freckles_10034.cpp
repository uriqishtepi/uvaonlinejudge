/* connect dots to minimize ink
 * this is an mst problem
 */
#include<map>
#include<stdio.h>
#include<math.h>
#include<assert.h>
#define MAX 100
#define pi std::pair<int, int>
#define mi std::multimap<double, pi >

double mst(double arr[][2], double D[][MAX+1], int n)
{
    //start from any point, will connect to the nearest only
    //need a priority queue here
    mi q;
    bool visited[MAX+1] = {0};
    for(int i = 1; i < n; i++)
        q.insert(std::make_pair(D[0][i] , std::make_pair(0,i)));
    visited[0] = 1;
    double tot = 0.0;
    while(! q.empty() )
    {
        pi p = q.begin()->second;
        double d = sqrt(q.begin()->first);
        q.erase(q.begin());

        int curr = p.second;
        if(visited[curr]) continue;

        tot += d;
        //printf("getting link %d-%d with d=%lf, res=%lf\n", p.first, p.second, d, tot);
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
    char buff[2048];
    fgets(buff, 2047, stdin);
    sscanf(buff, "%d", &cases);
    assert(cases > 0);

    while(cases-- > 0) {
        double arr[MAX+1][2] = {{0}};
        double D[MAX+1][MAX+1] = {{0}};
        fgets(buff, 2047, stdin); //empty line

        fgets(buff, 2047, stdin); 
        int n;
        sscanf(buff, "%d", &n);
        assert(n > 0 && n <= MAX);
        int i = 0;
        while(i < n) {
            double a, b;
            fgets(buff, 2047, stdin); 
            int offset;
            sscanf(buff, "%lf%n", &a, &offset);
            sscanf(buff+offset, "%lf", &b);
            arr[i][0] = a;
            arr[i][1] = b;
            //printf("read %lf %lf\n", a, b);
            int j;
            for(j=0;j<i;j++) {
                double dx = arr[i][0] - arr[j][0];
                double dy = arr[i][1] - arr[j][1];
                double d = dx*dx + dy*dy;
                D[j][i] = d;
                D[i][j] = d;
            }

            i++;
        }
        printf("%.2lf\n", mst(arr, D, n));
    }
    return 1;
}
