#pragma once

#include"Step.h"
#include"Context.h"
#include"ConsoleManager.h"

class SubStep {
public:
    virtual std::unique_ptr<SubStep> execute(Context &) = 0;
    virtual ~SubStep() = default;
protected:
    ConsoleManager reader;
};

class SubStepTitle : public SubStep {
public:
    std::unique_ptr<SubStep> execute(Context &) override;
};

class SubStepPriority : public SubStep {
public:
    std::unique_ptr<SubStep> execute(Context &) override;
};

class SubStepTime : public SubStep {
public:
    std::unique_ptr<SubStep> execute(Context &) override;
};