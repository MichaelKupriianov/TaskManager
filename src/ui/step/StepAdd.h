#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfCommand.h"
#include"Context.h"

class StepAdd : public Step {
public:
    StepAdd();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
private:
    const TypeOfCommand command_;
};

class StepAddSub : public Step {
public:
    StepAddSub();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
private:
    const TypeOfCommand command_;
};