#pragma once

#include <memory>
#include "step/Step.h"
#include "step/StepAdd.h"
#include "step/StepEdit.h"
#include "step/StepShow.h"
#include "step/TypeOfStep.h"

class Factory {
public:
    virtual std::shared_ptr<Step> CreateStep(TypeOfStep);
    virtual std::shared_ptr<Step> GetRootStep();

    virtual ~Factory() = default;
};
