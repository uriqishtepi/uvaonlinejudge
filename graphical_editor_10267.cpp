#include<stdio.h>
#include <string.h>
#include<queue>
#include<utility>
#include<assert.h>
#define pi std::pair<int,int> 
#define qpi std::queue< pi >

//#define out printf
#define out 


void fillCell(int newi, int newj, int m, int n, char image[250][250], qpi & q, char origC, char newC) 
{
    if(newj >= 1 && newi >= 1 && newj <= n && newi <= m 
            && image[newj-1][newi - 1] == origC)
    {
        image[newj-1][newi-1] = newC;
        q.push(std::make_pair(newi,newj));
    }
}

int main()
{
    char buff[1024];
    char image[250][250];
    char cmd;
    int m = 0;
    int n = 0;
    while(scanf("%c ", &cmd) != EOF && cmd != 'X') {
        out("c=%c\n", cmd);
        switch(cmd) {
          case '\n': continue;
          case 'I': 
            {
                int i;
                memset(image, 0, sizeof(image)); 
                scanf("%d %d", &m, &n);
                out("%d %d", m, n);

                for(i = 0; i < n; i++) 
                    memset(image[i], 'O', m* sizeof(char)); 
            }
            break;
          case 'C': 
            {
                int i;
                for(i = 0; i < n; i++) 
                    memset(image[i], 'O', m* sizeof(char)); 
            }
            break;
          case 'L': 
            {
                int x, y;
                char c;
                scanf("%d %d %c", &x, &y, &c);
                image[y-1][x-1] = c;
            }
            break;
          case 'V': 
            {
                int x, y1, y2;
                char c;
                scanf("%d %d %d %c", &x, &y1,&y2,&c);
                out("%d %d %d %c", x, y1, y2, c);
                int i;
                for(i = y1; i <= y2; i++) 
                    image[i-1][x-1] = c;
            }
            break;
          case 'H': 
            {
                int x1, x2, y;
                char c;
                scanf("%d %d %d %c", &x1, &x2, &y,&c);
                out("%d %d %d %c", x1, x2, y, c);
                int j;
                for(j = x1; j <= x2; j++) 
                    image[y-1][j-1] = c;
            }break;
          case 'K': 
            {
                int x1,x2,y1,y2;
                char c;
                scanf("%d %d %d %d %c", &x1, &y1, &x2,&y2,&c);
                out("%d %d %d %d %c", x1, y1, x2,y2, c);
                assert(x1 <= x2);
                assert(y1 <= y2);
                int i, j;
                for(i = y1; i <= y2; i++) {
                    for(j = x1; j <= x2; j++) {
                        image[i-1][j-1] = c;
                    }
                    out("\n");
                }
            }
            break;
          case 'F': 
            {
                int x, y;
                char c;
                scanf("%d %d %c", &x, &y, &c);
                int origC = image[y-1][x-1];
                if(origC == c) { 
                    printf("%d %d %c same as toFill\n", x, y, c);
                    break; //no need to do anything
                }

                qpi q;
                q.push(std::make_pair(y,x));
                image[y-1][x-1] = c;
                while(!q.empty()){
                    pi p = q.front();
                    q.pop();
                    int i = p.first;
                    int j = p.second;
                    fillCell(i-1, j, m, n, image, q, origC, c);
                    fillCell(i, j-1, m, n, image, q, origC, c);
                    fillCell(i+1, j, m, n, image, q, origC, c);
                    fillCell(i, j+1, m, n, image, q, origC, c);
                }
            }
            break;
          case 'S': 
            {
                gets(buff); //chew rest of line
                printf("%s\n", buff);
                int i, j;
                for(i = 0; i < n; i++) {
                    for(j = 0; j < m; j++) {
                        printf("%c", image[i][j]);
                    }
                    printf("\n");
                }
            }
            break;
          default : 
            gets(buff);
            continue;
        }
    }

    return 0;
}
