#include"StepShow.h"
#include"Dependency.h"
#include"SortBy.h"

StepShow::StepShow() : command_{TypeOfCommand::SHOW} {}

std::shared_ptr<Step> StepShow::execute(Context &context,
                                        const std::shared_ptr<Dependency> &dependency) {
    bool print_subtasks{dependency->view()->ReadIfPrintSubtasks(command_)};
    SortBy sort_by{dependency->view()->ReadSortBy(command_)};
    context.set_command(std::shared_ptr<Command>(new CommandShow{print_subtasks,
                                                                 sort_by, dependency->view()}));
    return dependency->factory()->GetRootStep();
}

StepShowTask::StepShowTask() : command_{TypeOfCommand::SHOW_TASK} {}

std::shared_ptr<Step> StepShowTask::execute(Context &context,
                                            const std::shared_ptr<Dependency> &dependency) {
    TaskId id{dependency->view()->ReadId(command_)};
    SortBy sort_by{dependency->view()->ReadSortBy(command_)};
    context.set_command(std::shared_ptr<Command>(new CommandShowTask{id,
                                                                 sort_by, dependency->view()}));
    return dependency->factory()->GetRootStep();
}

StepShowLabel::StepShowLabel() : command_{TypeOfCommand::SHOW_LABEL} {}

std::shared_ptr<Step> StepShowLabel::execute(Context &context,
                                             const std::shared_ptr<Dependency> &dependency) {
    std::string label{dependency->view()->ReadLabel(command_)};
    SortBy sort_by{dependency->view()->ReadSortBy(command_)};
    context.set_command(std::shared_ptr<Command>(new CommandShowLabel{label,
                                                                     sort_by, dependency->view()}));
    return dependency->factory()->GetRootStep();
}