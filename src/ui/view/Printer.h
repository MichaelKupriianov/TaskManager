#pragma once

#include<string>

class Printer {
public:
    virtual void PrintString(const std::string &);

    virtual ~Printer() = default;
};
