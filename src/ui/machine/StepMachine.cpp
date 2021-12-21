#include "StepMachine.h"
#include "step/Step.h"
#include "context/Context.h"

StepMachine::StepMachine(const std::shared_ptr<DependencyForSteps> &dependency) :
        dependency_{dependency} {}

std::shared_ptr<Command> StepMachine::GetCommand() {
    std::shared_ptr<Step> step_{dependency_->factory()->GetRootStep()};
    Context context;
    while (!context.command()) {
        step_ = step_->execute(context, dependency_);
    }
    return context.command();
}