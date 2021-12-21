#pragma once

#include <memory>
#include "Step.h"
#include "context/Context.h"

class StepAdd : public Step {
public:
    StepAdd();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};

class StepAddSub : public Step {
public:
    StepAddSub();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};