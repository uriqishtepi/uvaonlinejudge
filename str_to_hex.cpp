#include <stdio.h>
#include <iostream>
#include <string>


const char hex[] = "0123456789abcdef";
int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage:"<< argv[0] << " <param>" << std::endl;
        exit (0);
    }

    std::string str(argv[1]);   
    std::cout << "STR: " << str << std::endl;
    for (auto it = str.begin(); it != str.end(); it++)
        printf("%c%c", hex[(*it & 0xf0) >> 4], hex[*it & 0x0f]);
    return 0;
}
