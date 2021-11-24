#pragma once

#include<string>
#include<memory>
#include"Step.h"
#include"SubStep.h"

class Factory {
public:
    static std::unique_ptr<Step> CreateStep(const std::string &);
    static std::unique_ptr<SubStep> CreateSubStep(const std::string &state);
};
