#pragma once

#include<memory>
#include"Context.h"
#include"ConsoleManager.h"
#include"TypeOfStep.h"

class Step {
public:
    virtual std::unique_ptr<Step> execute(Context &) = 0;
    virtual ~Step() = default;
};

class StepRoot : public Step {
public:
    StepRoot() : console_manager_(TypeOfStep::ROOT) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepQuit : public Step {
public:
    StepQuit() : console_manager_(TypeOfStep::QUIT) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepHelp : public Step {
public:
    StepHelp() : console_manager_(TypeOfStep::HELP) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepComplete : public Step {
public:
    StepComplete() : console_manager_(TypeOfStep::COMPLETE) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepDelete : public Step {
public:
    StepDelete() : console_manager_(TypeOfStep::DELETE) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepLabel : public Step {
public:
    StepLabel() : console_manager_(TypeOfStep::LABEL) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};

class StepShow : public Step {
public:
    StepShow() : console_manager_(TypeOfStep::SHOW) {}
    std::unique_ptr<Step> execute(Context &) override;
private:
    ConsoleManager console_manager_;
};