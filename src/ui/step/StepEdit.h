#pragma once

#include<memory>
#include"Step.h"

class StepEdit : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override;
};
