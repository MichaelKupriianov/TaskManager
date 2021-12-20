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
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepRoot() = default;
};

class StepQuit : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepQuit() = default;
};

class StepHelp : public Step {
public:
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepHelp() = default;
};

class StepComplete : public Step {
public:
    StepComplete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepComplete() = default;
private:
    const TypeOfCommand command_;
};

class StepDelete : public Step {
public:
    StepDelete();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepDelete() = default;
private:
    const TypeOfCommand command_;
};

class StepSave : public Step {
public:
    StepSave();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepSave() = default;
private:
    const TypeOfCommand command_;
};

class StepLoad : public Step {
public:
    StepLoad();
    std::shared_ptr<Step> execute(Context &, const std::shared_ptr<Dependency> &) override;
    virtual ~StepLoad() = default;
private:
    const TypeOfCommand command_;
};