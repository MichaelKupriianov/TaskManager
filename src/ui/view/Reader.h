#pragma once

#include<string>

class Reader {
public:
    virtual std::string ReadString();

    virtual ~Reader() = default;
};