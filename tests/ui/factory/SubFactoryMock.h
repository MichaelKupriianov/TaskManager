#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"SubFactory.h"

class SubFactoryMock : public SubFactory {
public:
    MOCK_METHOD(std::shared_ptr<SubStep>, GetRootSubStep, (), (override));
    MOCK_METHOD(std::shared_ptr<SubStep>, GetNextSubStep, (const SubStepTitle &), (override));
    MOCK_METHOD(std::shared_ptr<SubStep>, GetNextSubStep, (const SubStepPriority &), (override));
    MOCK_METHOD(std::shared_ptr<SubStep>, GetNextSubStep, (const SubStepDate &), (override));
    MOCK_METHOD(std::shared_ptr<SubStep>, GetNextSubStep, (const SubStepLabel &), (override));
};