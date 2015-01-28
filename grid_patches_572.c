#include<stdio.h>

#define out printf

inline int isSet(char grid[100][100], int i, int j, int m, int n) {
    if(i >= 0 && j >=0 && i < m && j < n)
        return grid[i][j] == '@';

    return 0;
}

int main()
{
    int m, n;

    while(scanf("%d %d\n", &m, &n) != EOF && m != 0) {
        out("m %d n %d\n", m, n);
        int idCounter = 0;
        char grid[100][100];
        int id[100][100];
        int i, j;

        for(i=0;i<m;i++) {
            for(j=0;j<n;j++)
                scanf("%c", &grid[i][j]);
            scanf("\n");
        }

        for(i=0;i<m;i++) {
            for(j=0;j<n;j++)
                out("%c", grid[i][j]);
            out("\n");
        }


        for(i=0;i<m;i++) {
            for(j=0;j<n;j++){
                if(!isSet(grid, i, j, m, n)) continue;
                else if(isSet(grid, i-1, j-1, m, n)) id[i][j] = id[i-1][j-1];
                else if(isSet(grid, i-1, j, m, n)) id[i][j] = id[i-1][j];
                else if(isSet(grid, i-1, j+1, m, n)) id[i][j] = id[i-1][j+1];
                else if(isSet(grid, i, j-1, m, n)) id[i][j] = id[i][j-1];
                else id[i][j] = ++idCounter;
            }
        }
        printf("%d\n", idCounter);
    }


    return 0;
}
