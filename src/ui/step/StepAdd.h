#pragma once

#include<memory>
#include"Step.h"

class StepAdd : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override;
};
