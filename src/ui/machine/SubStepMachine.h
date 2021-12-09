#pragma once

#include<memory>
#include"SubDependency.h"
#include"Task.h"

class SubStepMachine {
public:
    explicit SubStepMachine(const std::shared_ptr<SubDependency> &);

    Task GetTask();
private:
    const std::shared_ptr<SubDependency> dependency_;
};
