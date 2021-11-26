#pragma once

#include<memory>
#include"Step.h"
#include"StepAdd.h"
#include"StepEdit.h"
#include"TypeOfStep.h"

class Factory {
public:
    static std::unique_ptr<Step> CreateStep(TypeOfStep);
    static std::unique_ptr<Step> GetRootStep();
};
