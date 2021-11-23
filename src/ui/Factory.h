#pragma once

#include<string>
#include<memory>
#include"State.h"

class Factory {
public:
    static std::unique_ptr<State> CreateState(const std::string &);
    static std::unique_ptr<State> CreateStateAdd(const std::string &);
};
