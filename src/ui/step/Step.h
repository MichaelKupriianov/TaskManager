#pragma once

#include<memory>
#include"Context.h"
#include"Reader.h"

class Step {
public:
    virtual std::unique_ptr<Step> execute(Context &) = 0;
protected:
    Reader reader;
};

class StepCommand : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override;
};

class StepQuit : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override;
};

class StepHelp : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override;
};

class StepEdit : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override {}
};

class StepComplete : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override {}
};

class StepDelete : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override {}
};

class StepLabel : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override {}
};

class StepShow : public Step {
public:
    std::unique_ptr<Step> execute(Context &) override {}
};