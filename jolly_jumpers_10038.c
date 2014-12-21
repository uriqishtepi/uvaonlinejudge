#include <stdio.h>
#include <stdlib.h>
/*#define DEBUG true*/
#ifdef DEBUG
#define out printf
#else
#define out
#endif


int main ()
{
    char * buff = NULL;
    int count;
    size_t n;
    while((count = getline(&buff, &n, stdin)) > 0) {
        int numcount = 0;
        int advance = 0;
        int con;
        sscanf(buff + advance, "%d%n", &numcount, &con);
        advance += con;
        out("num %d\n",numcount);
        if(numcount == 1) {
            int num;
            con = sscanf(buff + advance, "%d ", &num);
            advance += con;
            out("num %d\n",num);
            if(-9 <= num && num <= 9) 
                printf("Jolly\n");
            else
                printf("Not jolly\n");

            continue;
        }

        char hash[3001] = {0};
        int num;
        int prev;
        int count = 0;
            
        while((sscanf(buff + advance, "%d%n", &num, &con)) != EOF) {
            if(count++ > 0) {
                hash[abs(prev - num)] = 1;
            }
            out("numa %d advance=%d\n",num, advance);
            prev = num;
            advance += con;
        }
        size_t i;
        int jcount = 0;
        for(i = 1; i < numcount; i++)
            jcount += hash[i];
        out("%d\n", jcount);
        if(jcount >= numcount - 1)
            printf("Jolly\n");
        else
            printf("Not jolly\n");
    }
    return 0;
}
