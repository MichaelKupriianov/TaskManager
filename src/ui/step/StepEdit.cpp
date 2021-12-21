#include "StepEdit.h"
#include "dependency/DependencyForSteps.h"
#include "machine/SubStepMachine.h"
#include "factory/SubFactory.h"
#include "Task.pb.h"

StepEdit::StepEdit() : command_{TypeOfStep::EDIT} {}

std::shared_ptr<Step> StepEdit::execute(Context &context, const std::shared_ptr<DependencyForSteps> &dependency) {
    TaskId id{dependency->view()->ReadId(command_)};
    std::shared_ptr<SubFactory> sub_factory{new SubFactory};
    std::shared_ptr<DependencyForSubSteps> sub_dependency{new DependencyForSubSteps{sub_factory, dependency->view(), command_}};
    SubStepMachine sub_machine{sub_dependency};
    Task task = *sub_machine.GetTask();
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandEdit{
                id, task, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}
