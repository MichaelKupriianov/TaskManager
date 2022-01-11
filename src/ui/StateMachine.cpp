#include "StateMachine.h"
#include "step/Step.h"

namespace ui {
    StateMachine::StateMachine(const std::shared_ptr<step::Resources>& resources) :
            resources_{resources} {}

    void StateMachine::Run(Context& context) {
        auto step = resources_->factory->GetInitialStep();
        while (!context.has_command())
            step = step->execute(context, resources_);
    }

    void StateMachine::Run(SubContext& context) {
        auto step = resources_->factory->GetInitialSubStep();
        while (!context.if_finished())
            step = step->execute(context, resources_);
    }
}