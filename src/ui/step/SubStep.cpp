#include"SubStep.h"
#include"SubDependency.h"
#include"Task.h"

std::unique_ptr<SubStep> SubStepTitle::execute(SubContext &context,
                                               const std::shared_ptr<SubDependency> &dependency) {
    const std::string title(dependency->view()->ReadTitle(dependency->command()));
    context.set_task(Task::Arguments::Create(title));
    return dependency->factory()->GetNextSubStep(*this);
}

std::unique_ptr<SubStep>
SubStepPriority::execute(SubContext &context,
                         const std::shared_ptr<SubDependency> &dependency) {
    Task::Priority priority(dependency->view()->ReadPriority(dependency->command()));
    context.set_task(Task::Arguments::Create(context.task_title(), priority));
    return dependency->factory()->GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepDate::execute(SubContext &context,
                                              const std::shared_ptr<SubDependency> &dependency) {
    const time_t date(dependency->view()->ReadDate(dependency->command()));
    context.set_task(Task::Arguments::Create(context.task_title(), context.task_priority(), date));
    return dependency->factory()->GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepLabel::execute(SubContext &context,
                                               const std::shared_ptr<SubDependency> &dependency) {
    const std::string label(dependency->view()->ReadLabel(dependency->command()));
    context.set_task(Task::Arguments::Create(context.task_title(), context.task_priority(),
                                             context.task_date(), label));
    context.finished();
    return dependency->factory()->GetNextSubStep(*this);
}