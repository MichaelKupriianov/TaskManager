#include"StepAdd.h"
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<Step> StepAdd::execute(Context &context) {
    std::unique_ptr<Step> state(Factory::CreateSubStep("title"));
    context.setAddFinished(false);

    while (!context.add_finished()) {
        state = std::move(state->execute(context));
    }
    if (!reader.Confirm()) context.setTask("..");
    return Factory::CreateStep("command");
}

std::unique_ptr<Step> StepAddTitle::execute(Context &context) {
    const std::string title(reader.ReadTitle("Add"));
    try {
        context.setTask(title);
        return Factory::CreateSubStep("priority");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("title");
    }
}

std::unique_ptr<Step> StepAddPriority::execute(Context &context) {
    const std::string priority(reader.ReadPriority("Add"));
    try {
        context.setTask(context.task_title(), StringToPriority(priority));
        return Factory::CreateSubStep("time");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("priority");
    }
}

std::unique_ptr<Step> StepAddTime::execute(Context &context) {
    const std::string time(reader.ReadTime("Add"));
    try {
        context.setTask(context.task_title(), context.task_priority(), StringToTime(time));
        context.setAddFinished(true);
        return Factory::CreateSubStep("time");
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateSubStep("time");
    }
}