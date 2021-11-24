#include"SubStep.h"
#include<stdexcept>
#include<memory>
#include"Factory.h"

std::unique_ptr<SubStep> SubStepId::execute(Context &context) {
    const int task_id(reader.ReadId(context.current_step()));
    context.set_id(task_id);
    return Factory::CreateSubStep("title");
}

std::unique_ptr<SubStep> SubStepTitle::execute(Context &context) {
    const std::string title(reader.ReadTitle(context.current_step()));
    try {
        context.set_task({title});
        return Factory::CreateSubStep("priority");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("title");
    }
}

std::unique_ptr<SubStep> SubStepPriority::execute(Context &context) {
    const std::string priority(reader.ReadPriority(context.current_step()));
    try {
        context.set_task({context.task_title(), StringToPriority(priority)});
        return Factory::CreateSubStep("time");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("priority");
    }
}

std::unique_ptr<SubStep> SubStepTime::execute(Context &context) {
    const std::string time(reader.ReadTime(context.current_step()));
    try {
        context.set_task({context.task_title(), context.task_priority(), StringToTime(time)});
        context.set_local_finished(true);
        return Factory::CreateSubStep("time");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("time");
    }
}