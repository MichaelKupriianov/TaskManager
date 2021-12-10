#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"TaskManager.h"

class TaskManagerMock : public TaskManager {
public:
    MOCK_METHOD(bool, AddTask, (const Task &), (override));
};