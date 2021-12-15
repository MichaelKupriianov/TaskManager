#include"SubStepMachine.h"
#include"SubContext.h"
#include"SubStep.h"

SubStepMachine::SubStepMachine(const std::shared_ptr<SubDependency> &dependency) :
        dependency_{dependency} {}

std::shared_ptr<Task> SubStepMachine::GetTask() {
    SubContext sub_context;
    std::unique_ptr<SubStep> step{dependency_->factory()->GetRootSubStep()};
    while (!sub_context.if_finished()) {
        step = std::move(step->execute(sub_context, dependency_));
    }
    return sub_context.task();
}