#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfStep.h"

class Factory {
public:
    std::unique_ptr<Step> CreateStep(TypeOfStep);
    std::unique_ptr<Step> GetRootStep();
};
