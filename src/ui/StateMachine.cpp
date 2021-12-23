#include "StateMachine.h"
#include "step/Step.h"

namespace ui {
    StateMachine::StateMachine(const std::shared_ptr<step::Resources>& dependency) :
            dependency_{dependency} {}

    void StateMachine::Run(Context& context) {
        auto step = dependency_->factory->GetInitialStep();
        while (!context.has_command())
            step = step->execute(context, dependency_);
    }

    void StateMachine::Run(SubContext& context) {
        auto step = dependency_->factory->GetInitialSubStep();
        while (!context.if_finished())
            step = step->execute(context, dependency_);
    }
}