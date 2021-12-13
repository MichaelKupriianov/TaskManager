#pragma once

#include<memory>
#include"Step.h"
#include"StepAdd.h"
#include"StepEdit.h"
#include"StepShow.h"
#include"TypeOfStep.h"

class Factory {
public:
    virtual std::shared_ptr<Step> CreateStep(TypeOfStep);
    virtual std::shared_ptr<Step> GetRootStep();

    virtual ~Factory() = default;
};
