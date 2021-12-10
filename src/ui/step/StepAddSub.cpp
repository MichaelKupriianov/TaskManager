#include"StepAddSub.h"
#include"Dependency.h"
#include"SubStepMachine.h"
#include"SubFactory.h"
#include"Task.h"

StepAddSub::StepAddSub() : command_{TypeOfCommand::ADDSUB} {}

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
