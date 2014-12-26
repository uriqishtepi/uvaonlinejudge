#include<stdio.h>

int main()
{
    char * buff = NULL;
    size_t sz;
    int image [250][250] = {0};
    while(getline(buff, &sz, stdin) > 0) {
        char * tok = strtok(buff, " \n");
        char cmd = tok[0];

        switch(cmd) {
          case I: 
            tok = strtok(NULL, " \n");
            int m = atoi(tok);
              
            tok = strtok(NULL, " \n");
            int n = atoi(tok);
            memset(0, );
            break;
          case C: 
            break;
          case L: 
            break;
          case V: 
            break;
          case H: 
            break;
          case K: 
            break;
          case F: 
            break;
          case S: 
            break;
          case X:
            break;
          default : continue;
        }
    }

    return 0;
}
