#pragma once

#include<memory>
#include"SubContext.h"

class SubDependency;

class SubStep {
public:
    virtual std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
    virtual ~SubStepTitle() = default;
};

class SubStepPriority : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
    virtual ~SubStepPriority() = default;
};

class SubStepDate : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
    virtual ~SubStepDate() = default;
};

class SubStepLabel : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<SubDependency> &) override;
    virtual ~SubStepLabel() = default;
};