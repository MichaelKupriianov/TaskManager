#pragma once

#include <memory>
#include "Step.h"
#include "context/Context.h"

class StepShow : public Step {
public:
    StepShow();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};

class StepShowTask : public Step {
public:
    StepShowTask();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};

class StepShowLabel : public Step {
public:
    StepShowLabel();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
private:
    const TypeOfStep command_;
};