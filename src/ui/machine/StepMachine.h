#pragma once

#include <memory>
#include "dependency/DependencyForSteps.h"
#include "controller/Command.h"

class StepMachine {
public:
    explicit StepMachine(const std::shared_ptr<DependencyForSteps> &);

    virtual std::shared_ptr<Command> GetCommand();

    virtual ~StepMachine() = default;
private:
    const std::shared_ptr<DependencyForSteps> dependency_;
};
