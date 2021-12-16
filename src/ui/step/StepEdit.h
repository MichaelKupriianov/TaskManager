#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfCommand.h"
#include"Context.h"

class StepEdit : public Step {
public:
    StepEdit();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
private:
    const TypeOfCommand command_;
};