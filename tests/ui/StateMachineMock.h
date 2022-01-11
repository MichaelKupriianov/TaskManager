#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/StateMachine.h"

class StateMachineMock : public ui::StateMachine {
public:
    StateMachineMock(const std::shared_ptr<ui::step::Resources> &resources) : StateMachine(resources) {}
};