#include"StepAdd.h"
#include"Dependency.h"
#include"SubStepMachine.h"
#include"SubFactory.h"
#include"Task.h"

StepAdd::StepAdd() : command_{TypeOfCommand::ADD} {}

std::shared_ptr<Step> StepAdd::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    std::shared_ptr<SubFactory> sub_factory{new SubFactory};
    std::shared_ptr<SubDependency> sub_dependency{new SubDependency{sub_factory, dependency->view(), command_}};
    SubStepMachine sub_machine{sub_dependency};
    Task task = sub_machine.GetTask();
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandAdd{
                task, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}

StepAddSub::StepAddSub() : command_{TypeOfCommand::ADD_SUB} {}

std::shared_ptr<Step> StepAddSub::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    TaskId parent_id{dependency->view()->ReadParentId(command_)};
    std::shared_ptr<SubFactory> sub_factory{new SubFactory};
    std::shared_ptr<SubDependency> sub_dependency{new SubDependency{sub_factory, dependency->view(), command_}};
    SubStepMachine sub_machine{sub_dependency};
    Task task = sub_machine.GetTask();
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandAddSub{
                task, parent_id, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}
