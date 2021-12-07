#pragma once

#include<memory>
#include"Factory.h"

class StepMachine {
public:
    explicit StepMachine(std::shared_ptr<Factory> &);

    Context Run();
private:
    std::shared_ptr<Factory> factory_;
};
