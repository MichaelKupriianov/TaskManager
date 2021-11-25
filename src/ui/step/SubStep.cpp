#include"SubStep.h"
#include<stdexcept>
#include<memory>
#include"Factory.h"

std::unique_ptr<SubStep> SubStepTitle::execute(Context &context) {
    const std::string title(reader.ReadTitle(context.current_step()));
    context.set_task({title});
    return Factory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepPriority::execute(Context &context) {
    Task::Priority priority(reader.ReadPriority(context.current_step()));
    context.set_task({context.task_title(), priority});
    return Factory::GetNextSubStep(*this);
}

std::unique_ptr<SubStep> SubStepTime::execute(Context &context) {
    const time_t time(reader.ReadTime(context.current_step()));
    context.set_task({context.task_title(), context.task_priority(), time});
    context.set_local_finished(true);
    return Factory::GetNextSubStep(*this);
}