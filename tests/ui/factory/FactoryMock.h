#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Factory.h"

class FactoryMock : public Factory {
public:
    MOCK_METHOD(std::shared_ptr<Step>, CreateStep, (TypeOfStep), (override));
    MOCK_METHOD(std::shared_ptr<Step>, GetRootStep, (), (override));
};
