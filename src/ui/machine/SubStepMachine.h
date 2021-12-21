#pragma once

#include <memory>
#include "dependency/DependencyForSubSteps.h"
#include "Task.pb.h"

class SubStepMachine {
public:
    explicit SubStepMachine(const std::shared_ptr<DependencyForSubSteps> &);

    virtual std::shared_ptr<Task> GetTask();

    virtual ~SubStepMachine() = default;
private:
    const std::shared_ptr<DependencyForSubSteps> dependency_;
};
