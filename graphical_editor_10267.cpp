#include<stdio.h>
#include <string.h>
#include<queue>
#include<utility>
#include<assert.h>
#define pi std::pair<int,int> 
#define qpi std::queue< pi >

//#define out printf
#define out 

void fillCell(int newi, int newj, int n, int m, char image[251][251], 
              qpi & q, char origC, char newC) 
{
    if(newj >= 1 && newi >= 1 && newj <= m && newi <= n 
            && image[newi-1][newj - 1] == origC) {
        image[newi-1][newj-1] = newC;
        q.push(std::make_pair(newj, newi));
    }
}

int main()
{
    char buff[2024];
    char image[251][251] = {{0}};
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
                int min_y, max_y;
                if(y1 < y2) { 
                    min_y = y1;
                    max_y = y2;
                } else {
                    min_y = y2;
                    max_y = y1;
                }
                for(i = min_y; i <= max_y; i++) 
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
                int min_x, max_x;
                if(x1 < x2) { 
                    min_x = x1;
                    max_x = x2;
                } else {
                    min_x = x2;
                    max_x = x1;
                }
                for(j = min_x; j <= max_x; j++) 
                    image[y-1][j-1] = c;
            }break;
          case 'K': 
            {
                int x1,x2,y1,y2;
                char c;
                scanf("%d %d %d %d %c", &x1, &y1, &x2,&y2,&c);
                out("%d %d %d %d %c", x1, y1, x2,y2, c);
                int min_x, max_x;
                if(x1 < x2) { 
                    min_x = x1;
                    max_x = x2;
                } else {
                    min_x = x2;
                    max_x = x1;
                }
                int min_y, max_y;
                if(y1 < y2) { 
                    min_y = y1;
                    max_y = y2;
                } else {
                    min_y = y2;
                    max_y = y1;
                }
                int i, j;
                for(i = min_y; i <= max_y; i++) {
                    for(j = min_x; j <= max_x; j++) {
                        image[i-1][j-1] = c;
                    }
                    out("\n");
                }
            }
            break;
          case 'F': 
            {
                int x, y;
                char newC;
                scanf("%d %d %c", &x, &y, &newC);
                int origC = image[y-1][x-1];
                if(origC == newC) { 
                    break; //no need to do anything
                }

                qpi q;
                fillCell(y, x, n, m, image, q, origC, newC);
                while(!q.empty()){
                    pi p = q.front();
                    q.pop();
                    int i = p.second;
                    int j = p.first;
                    fillCell(i-1, j, n, m, image, q, origC, newC);
                    fillCell(i+1, j, n, m, image, q, origC, newC);
                    fillCell(i, j-1, n, m, image, q, origC, newC);
                    fillCell(i, j+1, n, m, image, q, origC, newC);
                }
            }
            break;
          case 'S': 
            {
                gets(buff); //chew rest of line
                printf("%s\n", buff);
                int i;
                for(i = 0; i < n; i++) {
                    printf("%s\n", image[i]);
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
