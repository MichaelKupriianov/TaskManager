#pragma once

#include<memory>
#include"Step.h"
#include"Context.h"
#include"TypeOfCommand.h"

class StepShow : public Step {
public:
    StepShow();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};

class StepShowTask : public Step {
public:
    StepShowTask();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};

class StepShowLabel : public Step {
public:
    StepShowLabel();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};