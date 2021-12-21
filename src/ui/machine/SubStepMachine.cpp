#include "machine/SubStepMachine.h"
#include "context/SubContext.h"
#include "step/SubStep.h"

SubStepMachine::SubStepMachine(const std::shared_ptr<DependencyForSubSteps> &dependency) :
        dependency_{dependency} {}

std::shared_ptr<Task> SubStepMachine::GetTask() {
    SubContext sub_context;
    std::shared_ptr<SubStep> step{dependency_->factory()->GetRootSubStep()};
    while (!sub_context.if_finished()) {
        step = step->execute(sub_context, dependency_);
    }
    return sub_context.task();
}