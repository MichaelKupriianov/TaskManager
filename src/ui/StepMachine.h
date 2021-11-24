#pragma once

#include<memory>
#include"Step.h"
#include"Factory.h"
#include"Context.h"

class StepMachine {
public:
    StepMachine() : state_(Factory::CreateStep("command")) {}

    void Doing();
private:
    std::unique_ptr<Step> state_;
    Context context_;
};
