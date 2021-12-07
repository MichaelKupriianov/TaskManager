#pragma once

#include<memory>
#include"Step.h"
#include"TypeOfStep.h"
#include"Reader.h"

class Factory {
public:
    explicit Factory(std::shared_ptr<Reader> &reader) : reader_(reader) {}

    std::unique_ptr<Step> CreateStep(TypeOfStep);
    std::unique_ptr<Step> GetRootStep();
private:
    std::shared_ptr<Reader> reader_;
};
