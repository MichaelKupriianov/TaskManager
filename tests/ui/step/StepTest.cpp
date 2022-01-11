//#include "gtest/gtest.h"
//#include "gmock/gmock.h"
//#include "ui/step/Step.h"
//#include "ui/step/Resources.h"
//#include "ui/view/ViewMock.h"
//#include "ui/FactoryMock.h"
//
//using ::testing::Return;
//using ::testing::AtLeast;
//using ::testing::InSequence;
//using ::testing::_;
//
//class StepRootTest : public ::testing::Test {
//public:
//    void SetUp() override {
//        auto reader = std::make_shared<Reader>();
//        auto printer = std::make_shared<Printer>();
//        view_ = std::make_shared<ViewMock>(reader, printer);
//        factory_ = std::shared_ptr<FactoryMock>(new FactoryMock);
//        dependency_ = std::make_shared<DependencyForStates>(factory_, view_);
//        step_ = std::make_shared<StepRoot>();
//    }
//
//protected:
//    std::shared_ptr<ViewMock> view_;
//    std::shared_ptr<Context> context_;
//    std::shared_ptr<FactoryMock> factory_;
//    std::shared_ptr<DependencyForStates> dependency_;
//    std::shared_ptr<StepRoot> step_;
//};
//
//TEST_F(StepRootTest, shouldWork) {
//    EXPECT_CALL(*view_, ReadCommand())
//            .Times(1)
//            .WillOnce(Return(TypeOfStep::QUIT));
//    EXPECT_CALL(*factory_, CreateStep(TypeOfStep::QUIT))
//            .Times(1)
//            .WillOnce(Return(std::shared_ptr<Step>{new StepQuit}));
//    EXPECT_TRUE(std::dynamic_pointer_cast<StepQuit>(
//            step_->execute(*context_, dependency_)));
//}
