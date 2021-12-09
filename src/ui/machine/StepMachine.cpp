#include"StepMachine.h"
#include"Step.h"
#include"Context.h"

StepMachine::StepMachine(const std::shared_ptr<Dependency> &dependency) :
        dependency_{dependency} {}

std::shared_ptr<Command> StepMachine::GetCommand() {
    std::unique_ptr<Step> step_{dependency_->factory()->GetRootStep()};
    Context context;
    while (!context.command()) {
        step_ = std::move(step_->execute(context, dependency_));
    }
    return context.command();
}