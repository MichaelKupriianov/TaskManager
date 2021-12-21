#pragma once

#include <memory>
#include "context/SubContext.h"

class DependencyForSubSteps;

class SubStep {
public:
    virtual std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<DependencyForSubSteps> &) = 0;
    virtual ~SubStep() = default;
};

class SubStepTitle : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<DependencyForSubSteps> &) override;
    virtual ~SubStepTitle() = default;
};

class SubStepPriority : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<DependencyForSubSteps> &) override;
    virtual ~SubStepPriority() = default;
};

class SubStepDate : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<DependencyForSubSteps> &) override;
    virtual ~SubStepDate() = default;
};

class SubStepLabel : public SubStep {
public:
    std::shared_ptr<SubStep> execute(SubContext &, const std::shared_ptr<DependencyForSubSteps> &) override;
    virtual ~SubStepLabel() = default;
};