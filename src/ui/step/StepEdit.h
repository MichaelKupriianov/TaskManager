#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfStep.h"
#include"Context.h"

class StepEdit : public Step {
public:
    StepEdit() : reader_(TypeOfStep::EDIT) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};
