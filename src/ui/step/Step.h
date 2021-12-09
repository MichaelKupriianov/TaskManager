#pragma once

#include<memory>
#include"Context.h"
#include"TypeOfCommand.h"

class Dependency;

class Step {
public:
    virtual std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) = 0;

    virtual ~Step() = default;
};

class StepRoot : public Step {
public:
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepQuit : public Step {
public:
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepHelp : public Step {
public:
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
};

class StepComplete : public Step {
public:
    StepComplete();
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};

class StepDelete : public Step {
public:
    StepDelete();
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};

class StepShow : public Step {
public:
    StepShow();
    std::unique_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &dependency) override;
private:
    const TypeOfCommand command_;
};