#pragma once

#include<memory>
#include"Context.h"
#include"TypeOfCommand.h"

class Dependency;

class Step {
public:
    virtual std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) = 0;

    virtual ~Step() = default;
};

class StepRoot : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepQuit : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepHelp : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepComplete : public Step {
public:
    StepComplete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};

class StepDelete : public Step {
public:
    StepDelete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};