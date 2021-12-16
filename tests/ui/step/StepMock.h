#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Step.h"

class StepRootMock : public StepRoot {
public:
    MOCK_METHOD(std::shared_ptr<Step>, execute,
                (Context & , const std::shared_ptr<Dependency> &), (override));
};

class StepQuitMock : public StepQuit {
public:
    MOCK_METHOD(std::shared_ptr<Step>, execute,
                (Context & , const std::shared_ptr<Dependency> &), (override));
};

class StepHelpMock : public StepHelp {
public:
    MOCK_METHOD(std::shared_ptr<Step>, execute,
                (Context & , const std::shared_ptr<Dependency> &), (override));
};

class StepCompleteMock : public StepComplete {
public:
    StepCompleteMock() : StepComplete{} {}
    MOCK_METHOD(std::shared_ptr<Step>, execute,
                (Context & , const std::shared_ptr<Dependency> &), (override));
};