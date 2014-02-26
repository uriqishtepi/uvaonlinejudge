#include<stdio.h>
#include<math.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include <string.h>
#include <iomanip>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


int countwin(char board[3][3], char c) {
    int count = 0;
    for(int i = 0; i < 3; i++) {
        //three horiz and three vert
        if(board[i][0] == c && board[i][1] == c && board[i][2] == c)
            count++;
        if(board[0][i] == c && board[1][i] == c && board[2][i] == c)
            count++;
    }
    if(board[2][0] == c && board[1][1] == c && board[0][2] == c)
        count++;
    if(board[0][0] == c && board[1][1] == c && board[2][2] == c)
        count++;
    return count;
}


int main(int argc, char **argv)
{
    out("Starting...\n");

    char str[21] = {0};
    char *buff = NULL;
    size_t sz;
    int n;
    scanf("%d\n",&n);
    for(int i = 0; i < n; i++) {
        char board[3][3] = {0};
        int xcount = 0;
        int ocount = 0;

        //read three game lines
        for(int j = 0; j < 3; j++) {
            if(getline(&buff, &sz, stdin) < 0) return 0;
            out("buff=%s\n", buff);

            for(int k = 0; k < 3; k++) {
                board[j][k] = buff[k];
                if(buff[k] == 'X') xcount++;
                else if(buff[k] == 'O') ocount++;
            }
        }


        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                out("%c",board[j][k]);
            }
            out("\n");
        } 

        int xwin = countwin(board, 'X');
        int owin = countwin(board, 'O');
        out("xwin=%d, owin=%d\n", xwin, owin);
        
        //process board
        int diff = std::abs(xcount - ocount);
        if(ocount > xcount || xcount - ocount > 1) {
            //can not have o moves to be more than x
            //and can not have x moves to be ahead more than 1
            printf("no\n");
        }
        else if(xwin == 1 && owin == 1) {
            //can not x and o both win 
            printf("no\n");
        }
        else if(xwin == 1 && xcount == ocount) {
            //can not have o have same moves as x if x won
            printf("no\n");
        }
        else if(owin == 1 && xcount > ocount) {
            //can not have x have more moves as o if o won
            printf("no\n");
        }
        else
            printf("yes\n");
        
        //and an empty line
        if(getline(&buff, &sz, stdin) < 0) break;
    }
    return 0;
}
