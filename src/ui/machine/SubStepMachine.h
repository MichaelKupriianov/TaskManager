#pragma once

#include<memory>
#include"SubDependency.h"
#include"Task.pb.h"

class SubStepMachine {
public:
    explicit SubStepMachine(const std::shared_ptr<SubDependency> &);

    std::shared_ptr<Task> GetTask();
private:
    const std::shared_ptr<SubDependency> dependency_;
};
