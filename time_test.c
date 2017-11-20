#include <string.h>
#include <stdio.h>

#include <time.h>



int main(int argc, char *argv[])

{

    const char *str = "2013-12-11 12:34:56";
    struct tm t;
    strptime(str, "%Y-%m-%d %H:%M:%S", &t);
    time_t t2 = mktime(&t);

    printf("time %d\n", t2);
    return 0;

}
