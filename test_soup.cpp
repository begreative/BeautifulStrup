#include "BeautifulStrup.h"
#include <iostream>
#include <string>
#include <stdlib.h>

void die(std::string s) { std::cout << s << "\n"; exit(EXIT_FAILURE); }

int main(int argc, char const *argv[])
{
    if(argc < 3)
        die("USAGE: ./test_soup <FILE.py> <DIRECTORY>");
    
    std::string f = argv[1];
    std::string d = argv[2];
    functions::find_invocations(f, "add", d);
     
    return 0;
}
