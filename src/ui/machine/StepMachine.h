#pragma once

#include<memory>
#include"Dependency.h"
#include"Command.h"

class StepMachine {
public:
    explicit StepMachine(const std::shared_ptr<Dependency> &);

    std::shared_ptr<Command> GetCommand();
private:
    const std::shared_ptr<Dependency> dependency_;
};
