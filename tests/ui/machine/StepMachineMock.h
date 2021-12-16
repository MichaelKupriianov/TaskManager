#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"StepMachine.h"

class StepMachineMock : public StepMachine {
public:
    StepMachineMock(const std::shared_ptr<Dependency> &dependency) : StepMachine(dependency) {}

    MOCK_METHOD(std::shared_ptr<Command>, GetCommand, (), (override));
};