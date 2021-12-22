#include "ui/StateMachine.h"
#include "step/Step.h"

namespace ui {
    StateMachine::StateMachine(const std::shared_ptr<step::Dependency>& dependency) :
            dependency_{dependency} {}

    std::shared_ptr<command::Command> StateMachine::GetCommand(Context& context) {
        std::shared_ptr<Step> step_{dependency_->factory->GetRootStep()};

        while (!context.has_command())
            step_ = step_->execute(context, dependency_);
        return context.command();
    }
}