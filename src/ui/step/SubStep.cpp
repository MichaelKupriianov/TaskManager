#include"SubStep.h"
#include<memory>
#include"SubFactory.h"
#include"Task.h"

SubStepTitle::SubStepTitle(std::shared_ptr<Reader> &reader, Command command) :
        reader_{reader}, command_{command} {}

std::unique_ptr<SubStep> SubStepTitle::execute(SubContext &context, std::shared_ptr<SubFactory> &factory) {
    const std::string title(reader_->ReadTitle(command_));
    context.set_task(Task::Arguments::Create(title));
    return factory->GetNextSubStep(*this);
}

SubStepPriority::SubStepPriority(std::shared_ptr<Reader> &reader, Command command) :
        reader_{reader}, command_{command} {}

std::unique_ptr<SubStep> SubStepPriority::execute(SubContext &context, std::shared_ptr<SubFactory> &factory) {
    Task::Priority priority(reader_->ReadPriority(command_));
    context.set_task(Task::Arguments::Create(context.task_title(), priority));
    return factory->GetNextSubStep(*this);
}

SubStepDate::SubStepDate(std::shared_ptr<Reader> &reader, Command command) :
        reader_{reader}, command_{command} {}

std::unique_ptr<SubStep> SubStepDate::execute(SubContext &context, std::shared_ptr<SubFactory> &factory) {
    const time_t date(reader_->ReadDate(command_));
    context.set_task(Task::Arguments::Create(context.task_title(), context.task_priority(), date));
    context.finished();
    return factory->GetNextSubStep(*this);
}