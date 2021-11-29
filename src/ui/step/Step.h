#pragma once

#include<memory>
#include"Context.h"
#include"Reader.h"
#include"TypeOfStep.h"

class Step {
public:
    virtual std::unique_ptr<Step> execute(Context &) = 0;
    virtual ~Step() = default;
};

class StepRoot : public Step {
public:
    StepRoot() : reader_(TypeOfStep::ROOT) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepQuit : public Step {
public:
    StepQuit() : reader_(TypeOfStep::QUIT) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepHelp : public Step {
public:
    StepHelp() : reader_(TypeOfStep::HELP) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepComplete : public Step {
public:
    StepComplete() : reader_(TypeOfStep::COMPLETE) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepDelete : public Step {
public:
    StepDelete() : reader_(TypeOfStep::DELETE) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepLabel : public Step {
public:
    StepLabel() : reader_(TypeOfStep::LABEL) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};

class StepShow : public Step {
public:
    StepShow() : reader_(TypeOfStep::SHOW) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    Reader reader_;
};