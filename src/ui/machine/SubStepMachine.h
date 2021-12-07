#pragma once

#include<memory>
#include"SubFactory.h"

class SubStepMachine {
public:
    explicit SubStepMachine(std::shared_ptr<SubFactory> &);

    SubContext Run();
private:
    std::shared_ptr<SubFactory> factory_;
};
