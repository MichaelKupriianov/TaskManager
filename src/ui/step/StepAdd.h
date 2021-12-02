#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfStep.h"
#include"Context.h"

class StepAdd : public Step {
public:
    StepAdd() : reader_(TypeOfStep::ADD) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};
