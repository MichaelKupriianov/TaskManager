#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfCommand.h"
#include"Context.h"

class StepAdd : public Step {
public:
    StepAdd();
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};