#include <stdio.h>
#include <assert.h>


typedef struct pair pair;
typedef struct moves moves;


struct pair {
    int x;
    int y;
};

struct moves {
    int depth; /* reached depth */
    int x; /* curr x and y */
    int y;
};

void allTrans(pair *p, int x, int y, int k)
{
    int newx = x;
    int newy = y;

    switch(k) {
    case 0: newx += 1; newy += 2; break;
    case 1: newx += 2; newy += 1; break;
    case 2: newx += 2; newy -= 1; break;
    case 3: newx += 1; newy -= 2; break;
    case 4: newx -= 1; newy -= 2; break;
    case 5: newx -= 2; newy -= 1; break;
    case 6: newx -= 2; newy += 1; break;
    case 7: newx -= 1; newy += 2; break;
    };
    p->x = newx;
    p->y = newy;
}

pair trans[8][8][8];
#define QSZ 200

void printTbl(int tbl[8][8])
{
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", tbl[i][j]);
        }
        printf("\n");
    }

}


int getNumSteps(int ox, int oy, int fx, int fy)
{
    if(ox == fx && oy == fy) return 0;

    moves m[QSZ];
    int visited[8][8] = {0};

    int front = 0;
    int end = 0;
    

    /* m will be used as que */
    moves g = { front+1, ox, oy };
    m[end++] = g;

    while (front != end && end < QSZ) {
        moves curr = m[front++];
        /* printf("pop %d %d \n ", curr.x, curr.y); */

        int k;
        for(k = 0; k < 8; k++) {
            pair p = trans[curr.x][curr.y][k];
           
            if(p.x == fx && p.y == fy) return curr.depth;

            if(p.x < 0 || p.y < 0 || p.x >= 8 || p.y >= 8 || visited[p.x][p.y])
                continue;
            moves g = { curr.depth + 1, p.x, p.y };
            m[end++] = g;
            visited[p.x][p.y] = 1;
        }
    }
}



int main()
{
    int i, j, k = 0;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                allTrans (&trans[i][j][k], i, j, k);
            }
        }
    }

    assert(trans[5][5][0].x == 6 && trans[5][5][0].y == 7);
    assert(trans[5][5][1].x == 7 && trans[5][5][1].y == 6);
    assert(trans[5][5][2].x == 7 && trans[5][5][2].y == 4);
    assert(trans[5][5][3].x == 6 && trans[5][5][3].y == 3);
    assert(trans[5][5][4].x == 4 && trans[5][5][4].y == 3);
    assert(trans[5][5][5].x == 3 && trans[5][5][5].y == 4);
    assert(trans[5][5][6].x == 3 && trans[5][5][6].y == 6);
    assert(trans[5][5][7].x == 4 && trans[5][5][7].y == 7);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                int x = trans[i][j][k].x;
                int y = trans[i][j][k].y;
                if(x < 0 || y < 0 || x >= 8 || y >= 8) continue;
                int nk = (k + 4) % 8;
                assert(trans[x][y][nk].x == i && trans[x][y][nk].y == j);
            }
        }
    }

    assert(getNumSteps(0,0,0,0) == 0);
    assert(getNumSteps(1,0,1,0) == 0);
    assert(getNumSteps(7,0,7,0) == 0);
    assert(getNumSteps(5,5,6,7) == 1);
    assert(getNumSteps(5,5,7,6) == 1);
    assert(getNumSteps(5,5,7,4) == 1);
    assert(getNumSteps(5,5,6,3) == 1);
    assert(getNumSteps(5,5,4,3) == 1);
    assert(getNumSteps(5,5,3,4) == 1);
    assert(getNumSteps(5,5,3,6) == 1);
    assert(getNumSteps(5,5,4,7) == 1);

    char a,b,c,d;
    while(scanf("%c%c %c%c\n", &a, &b, &c, &d) != EOF) {
        int origx = a-'a';
        int origy = b-'1';
        int finx = c-'a';
        int finy = d-'1';
        printf("To get from %c%c to %c%c " , a, b, c, d);
        printf("takes %d knight moves.\n", getNumSteps(origx, origy, finx, finy));

    }


    return 0;
}
