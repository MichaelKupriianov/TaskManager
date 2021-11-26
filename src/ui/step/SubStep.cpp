#include"SubStep.h"
#include<stdexcept>
#include<memory>
#include"SubFactory.h"
#include"Task.h"

std::unique_ptr<SubStep> SubStepTitle::execute(SubContext &context, const ConsoleManager &console_manager) {
    const std::string title(console_manager.ReadTitle());
    context.set_task(Task::Arguments::Create(title));
    return SubFactory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepPriority::execute(SubContext &context, const ConsoleManager &console_manager) {
    Task::Priority priority(console_manager.ReadPriority());
    context.set_task(Task::Arguments::Create(context.task_title(), priority));
    return SubFactory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepTime::execute(SubContext &context, const ConsoleManager &console_manager) {
    const time_t time(console_manager.ReadTime());
    context.set_task(Task::Arguments::Create(context.task_title(), context.task_priority(), time));
    context.finished();
    return SubFactory::GetNextSubStep(*this);
}