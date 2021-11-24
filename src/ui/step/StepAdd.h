#pragma once

#include<memory>
#include"Step.h"

class StepAdd : public Step {
public:
    virtual std::unique_ptr<Step> execute(Context &) override;
};

class StepAddTitle : public StepAdd {
public:
    std::unique_ptr<Step> execute(Context &) override;
};

class StepAddPriority : public StepAdd {
public:
    std::unique_ptr<Step> execute(Context &) override;
};

class StepAddTime : public StepAdd {
public:
    std::unique_ptr<Step> execute(Context &) override;
};
