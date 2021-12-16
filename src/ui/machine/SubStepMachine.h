#pragma once

#include<memory>
#include"SubDependency.h"
#include"Task.pb.h"

class SubStepMachine {
public:
    explicit SubStepMachine(const std::shared_ptr<SubDependency> &);

    virtual std::shared_ptr<Task> GetTask();

    virtual ~SubStepMachine() = default;
private:
    const std::shared_ptr<SubDependency> dependency_;
};
