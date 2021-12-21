#pragma once

#include <memory>
#include "Step.h"
#include "context/Context.h"

class StepEdit : public Step {
public:
    StepEdit();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};