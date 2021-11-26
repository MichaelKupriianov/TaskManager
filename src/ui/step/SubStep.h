#pragma once

#include"SubContext.h"
#include"ConsoleManager.h"

class SubStep {
public:
    virtual std::unique_ptr<SubStep> execute(SubContext &, const ConsoleManager &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const ConsoleManager &) override;
};

class SubStepPriority : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const ConsoleManager &) override;
};

class SubStepTime : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const ConsoleManager &) override;
};