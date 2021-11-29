#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfStep.h"
#include"Context.h"

class StepAdd : public Step {
public:
    StepAdd() : console_manager_(TypeOfStep::ADD) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader console_manager_;
};
