#include<sys/time.h>

int main() 
{
    struct timeval dt;
    gettimeofday(&dt, NULL);
    return 0;
}
