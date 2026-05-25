#include "hash/Md5.hpp"
#include <iostream>

int main() {
    Md5 md5;
    std::cout << "''               = " << md5.hash("")               << "\n";
    std::cout << "'a'              = " << md5.hash("a")              << "\n";
    std::cout << "'abc'            = " << md5.hash("abc")            << "\n";
    std::cout << "'message digest' = " << md5.hash("message digest") << "\n";
    return 0;
}