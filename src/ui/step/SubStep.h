#pragma once

#include<memory>
#include"SubContext.h"

class SubDependency;

class SubStep {
public:
    virtual std::unique_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
};

class SubStepPriority : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
};

class SubStepDate : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
};

class SubStepLabel : public SubStep {
public:
    std::unique_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
};