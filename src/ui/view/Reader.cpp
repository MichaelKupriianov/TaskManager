#include "Reader.h"
#include <iostream>

std::string Reader::ReadString() {
    std::string result;
    getline(std::cin, result);
    return result;
}
