#include"Step.h"
#include"Dependency.h"

std::shared_ptr<Step> StepRoot::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    TypeOfStep command(dependency->view()->ReadCommand());
    return dependency->factory()->CreateStep(command);
}

std::shared_ptr<Step> StepQuit::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    dependency->view()->Quit();
    context.set_command(std::shared_ptr<Command>{new CommandQuit});
    return dependency->factory()->GetRootStep();
}

std::shared_ptr<Step> StepHelp::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    dependency->view()->Help();
    return dependency->factory()->GetRootStep();
}

StepComplete::StepComplete() : command_{TypeOfCommand::COMPLETE} {}

std::shared_ptr<Step> StepComplete::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    TaskId id{dependency->view()->ReadId(command_)};
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>{new CommandComplete{id, dependency->view()}});
    }
    return dependency->factory()->GetRootStep();
}

StepDelete::StepDelete() : command_{TypeOfCommand::DELETE} {}

std::shared_ptr<Step> StepDelete::execute(Context &context, const std::shared_ptr<Dependency> &dependency) {
    TaskId id{dependency->view()->ReadId(command_)};
    if (dependency->view()->Confirm()) {
        context.set_command(std::shared_ptr<Command>(new CommandDelete{id, dependency->view()}));
    }
    return dependency->factory()->GetRootStep();
}