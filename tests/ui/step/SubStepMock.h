#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"SubStep.h"

class SubStepTitleMock : public SubStepTitle {
public:
    MOCK_METHOD(std::shared_ptr<SubStep>, execute,
                (SubContext & , const std::shared_ptr<SubDependency> &), (override));
};

class SubStepPriorityMock : public SubStepTitle {
public:
    MOCK_METHOD(std::shared_ptr<SubStep>, execute,
                (SubContext & , const std::shared_ptr<SubDependency> &), (override));
};

class SubStepDateMock : public SubStepTitle {
public:
    MOCK_METHOD(std::shared_ptr<SubStep>, execute,
                (SubContext & , const std::shared_ptr<SubDependency> &), (override));
};

class SubStepLabelMock : public SubStepTitle {
public:
    MOCK_METHOD(std::shared_ptr<SubStep>, execute,
                (SubContext & , const std::shared_ptr<SubDependency> &), (override));
};
