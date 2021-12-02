#include"SubStep.h"
#include<memory>
#include"SubFactory.h"
#include"Task.h"

std::unique_ptr<SubStep> SubStepTitle::execute(SubContext &context, const Reader &reader) {
    const std::string title(reader.ReadTitle());
    context.set_task(Task::Arguments::Create(title));
    return SubFactory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepPriority::execute(SubContext &context, const Reader &reader) {
    Task::Priority priority(reader.ReadPriority());
    context.set_task(Task::Arguments::Create(context.task_title(), priority));
    return SubFactory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepDate::execute(SubContext &context, const Reader &reader) {
    const time_t date(reader.ReadDate());
    context.set_task(Task::Arguments::Create(context.task_title(), context.task_priority(), date));
    context.finished();
    return SubFactory::GetNextSubStep(*this);
}