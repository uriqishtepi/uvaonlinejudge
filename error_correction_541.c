#include<stdio.h>
#define out 
/* #define out printf */

int main()
{

    int n;
    while(scanf("%d\n", &n) != EOF && n != 0) {
    
        int a[100][100] = {{0}};
        int i;
        int j;
        for(i=0;i<n;i++) {
            for(j=0;j<n;j++) {
                scanf("%d", &a[i][j]);
            }
        }        
        

        int rowdiscrepancycount = 0;
        int rowdiscrepancy = -1;
        for(i=0;i<n;i++) {
            int rowparity = 0;
            for(j=0;j<n;j++) {
                out("%d ", a[i][j]);
                rowparity += a[i][j];
            }
            out("\n");
            if(rowparity & 0x1) {
                rowdiscrepancycount++;
                rowdiscrepancy = i;
            }
            out("rowdiscrepancycount  %d\n", rowdiscrepancycount);
        }
        int coldiscrepancy = -1;
        int coldiscrepancycount = 0;
        if(rowdiscrepancycount <= 1) {
        for(j=0;j<n;j++) {
            int colparity = 0;
            for(i=0;i<n;i++) {
                out("%d ", a[i][j]);
                colparity += a[i][j];
            }
            out("\n");
            if(colparity & 0x1) {
                coldiscrepancycount++;
                coldiscrepancy = j;
            }
            out("coldiscrepancycount  %d\n", coldiscrepancycount);
        }
        }
        if(rowdiscrepancycount == 0 && coldiscrepancycount == 0)
            printf("OK\n");
        else if(rowdiscrepancycount == 1 || coldiscrepancycount == 1)
            printf("Change bit (%d,%d)\n", rowdiscrepancy+1, coldiscrepancy+1);
        else
            printf("Corrupt\n");
    }


    return 0;
}
