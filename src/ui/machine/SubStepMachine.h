#pragma once

#include<memory>
#include"SubStep.h"
#include"SubFactory.h"
#include"SubContext.h"
#include"Reader.h"

class SubStepMachine {
public:
    SubStepMachine() : state_(SubFactory::GetRootSubStep()) {}

    void Run(const Reader &);
private:
    std::unique_ptr<SubStep> state_;
    SubContext context_;
};
