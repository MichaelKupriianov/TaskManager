#pragma once

#include<string>
#include<memory>
#include"Step.h"

class Factory {
public:
    static std::unique_ptr<Step> CreateStep(const std::string &);
    static std::unique_ptr<Step> CreateSubStep(const std::string &state);
};
