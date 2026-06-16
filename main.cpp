#include "hash/Md5.hpp"
#include "hash/Sha1.hpp"
#include <iostream>

int main() {
    Md5 md5;
    Sha1 sha1;

    std::cout << "MD5 hash function\n";
    std::cout << "''               = " << md5.hash("")               << "\n";
    std::cout << "'a'              = " << md5.hash("a")              << "\n";
    std::cout << "'abc'            = " << md5.hash("abc")            << "\n";
    std::cout << "'message digest' = " << md5.hash("message digest") << "\n";

    std::cout << "\nSHA-1 hash function\n";
    std::cout << "''               = " << sha1.hash("")               << "\n";
    std::cout << "'a'              = " << sha1.hash("a")              << "\n";
    std::cout << "'abc'            = " << sha1.hash("abc")            << "\n";
    std::cout << "'message digest' = " << sha1.hash("message digest") << "\n";
    return 0;
}