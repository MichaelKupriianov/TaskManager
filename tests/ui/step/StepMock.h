//#pragma once
//
//#include "gtest/gtest.h"
//#include "gmock/gmock.h"
//#include "ui/step/Step.h"
//
//class StepRootMock : public ui::step::Root {
//public:
//    MOCK_METHOD(std::shared_ptr<ui::step::Step>, execute,
//                (ui::Context& , const std::shared_ptr<ui::step::Resources>&), (override));
//};
//
//class StepQuitMock : public ui::step::Quit {
//public:
//    MOCK_METHOD(std::shared_ptr<Step>, execute,
//                (ui::Context& , const std::shared_ptr<ui::step::Resources>&), (override));
//};
//
//class StepHelpMock : public ui::step::Help {
//public:
//    MOCK_METHOD(std::shared_ptr<Step>, execute,
//                (ui::Context& , const std::shared_ptr<ui::step::Resources>&), (override));
//};
//
//class StepCompleteMock : public ui::step::Complete {
//public:
//    StepCompleteMock() : ui::step::Complete{} {}
//    MOCK_METHOD(std::shared_ptr<Step>, execute,
//                (ui::Context& , const std::shared_ptr<ui::step::Resources>&), (override));
//};