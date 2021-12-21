#pragma once

#include <memory>
#include "context/Context.h"
#include "step/TypeOfStep.h"

class DependencyForSteps;

class Step {
public:
    virtual std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &dependency) = 0;

    virtual ~Step() = default;
};

class StepRoot : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepRoot() = default;
};

class StepQuit : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepQuit() = default;
};

class StepHelp : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepHelp() = default;
};

class StepComplete : public Step {
public:
    StepComplete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepComplete() = default;
private:
    const TypeOfStep command_;
};

class StepDelete : public Step {
public:
    StepDelete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepDelete() = default;
private:
    const TypeOfStep command_;
};

class StepSave : public Step {
public:
    StepSave();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepSave() = default;
private:
    const TypeOfStep command_;
};

class StepLoad : public Step {
public:
    StepLoad();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<DependencyForSteps> &) override;
    virtual ~StepLoad() = default;
private:
    const TypeOfStep command_;
};