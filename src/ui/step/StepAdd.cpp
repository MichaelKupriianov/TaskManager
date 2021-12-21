#include "StepAdd.h"
#include "dependency/DependencyForSteps.h"
#include "machine/SubStepMachine.h"
#include "factory/SubFactory.h"
#include "Task.pb.h"

StepAdd::StepAdd() : command_{TypeOfStep::ADD} {}

std::shared_ptr<Step> StepAdd::execute(Context &context, const std::shared_ptr<DependencyForSteps> &dependency) {
    std::shared_ptr<SubFactory> sub_factory{new SubFactory};
    std::shared_ptr<DependencyForSubSteps> sub_dependency{new DependencyForSubSteps{sub_factory, dependency->view(), command_}};
    SubStepMachine sub_machine{sub_dependency};
    Task task = *sub_machine.GetTask();
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandAdd{
                task, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}

StepAddSub::StepAddSub() : command_{TypeOfStep::ADD_SUB} {}

std::shared_ptr<Step> StepAddSub::execute(Context &context, const std::shared_ptr<DependencyForSteps> &dependency) {
    TaskId parent_id{dependency->view()->ReadParentId(command_)};
    std::shared_ptr<SubFactory> sub_factory{new SubFactory};
    std::shared_ptr<DependencyForSubSteps> sub_dependency{new DependencyForSubSteps{sub_factory, dependency->view(), command_}};
    SubStepMachine sub_machine{sub_dependency};
    Task task = *sub_machine.GetTask();
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandAddSub{
                task, parent_id, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}
