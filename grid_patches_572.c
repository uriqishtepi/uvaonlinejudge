#include<stdio.h>
#include<assert.h>

#define out 

inline int isSet(int grid[100][100], int i, int j, int m, int n) {
    if(i >= 0 && j >=0 && i < m && j < n)
        return grid[i][j] == '@';

    return 0;
}

/* breadth first search on this grid location 
 * caller sets this one node, then we only search its neigbors
*/
void bfs(int grid[100][100], int id[100][100], int m, int n, int i, int j)
{
    assert(isSet(grid, i, j, m, n) && id[i][j] > 0);
    /* printG(id, m, n); */

    int x, y;
    for(x=-1;x<2;x++){
        for(y=-1;y<2;y++){
            if(x == 0 && y == 0) continue;
            if(isSet(grid, i + x, j + y, m, n) && id[i + x][j + y] == 0) {
                id[i + x][j + y] = id[i][j];
                bfs(grid, id, m, n, i + x, j + y);
            }
        }
    }
}

void printG( int grid[100][100], int m, int n) {
int i, j;
        for(i=0;i<m;i++) {
            for(j=0;j<n;j++)
                out("%c", grid[i][j]);
            out("\n");
        }
}


int main()
{
    int m, n;
    while(scanf("%d %d\n", &m, &n) != EOF && m != 0) {
        out("m %d n %d\n", m, n);
        int idCounter = 0;
        int grid[100][100] = {{0}};
        int id[100][100] = {{0}};
        int i, j;

        for(i=0;i<m;i++) {
            for(j=0;j<n;j++)
                scanf("%c", &grid[i][j]);
            scanf("\n");
        }
        printG(grid, m, n);

        for(i=0;i<m;i++) {
            for(j=0;j<n;j++) {
                if(isSet(grid, i, j, m, n) && id[i][j] == 0) {
                    id[i][j] = ++idCounter;
                    bfs(grid, id, m, n, i, j);
                }
            }
        }
        printf("%d\n", idCounter);
    }
    return 0;
}
