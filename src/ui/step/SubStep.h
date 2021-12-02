#pragma once

#include"SubContext.h"
#include"Reader.h"

class SubStep {
public:
    virtual std::unique_ptr<SubStep> execute(SubContext &, const Reader &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const Reader &) override;
};

class SubStepPriority : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const Reader &) override;
};

class SubStepDate : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const Reader &) override;
};