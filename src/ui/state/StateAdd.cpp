#include"StateAdd.h"
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<State> StateAdd::execute(Context &context) {
    std::unique_ptr<State> state(Factory::CreateStateAdd("title"));
    context.setAddFinished(false);

    while (!context.add_finished()) {
        state = std::move(state->execute(context));
    }
    return Factory::CreateState("command");
}

std::unique_ptr<State> StateAddTitle::execute(Context &context) {
    const std::string title(Reader::ReadTitle("Add"));
    try {
        context.setTask(title);
        return Factory::CreateState("priority");
    }
    catch (const std::exception &exception) {
        Reader::HandleException(exception);
        return Factory::CreateState("title");
    }
}

std::unique_ptr<State> StateAddPriority::execute(Context &context) {
    const std::string priority(Reader::ReadPriority("Add"));
    try {
        context.setTask(context.task_title(), StringToPriority(priority));
        return Factory::CreateState("time");
    }
    catch (const std::exception &exception) {
        Reader::HandleException(exception);
        return Factory::CreateState("priority");
    }
}

std::unique_ptr<State> StateAddTime::execute(Context &context) {
    const std::string time(Reader::ReadTime("Add"));
    try {
        context.setTask(context.task_title(), context.task_priority(), StringToTime(time));
        context.setAddFinished(true);
        return Factory::CreateState("priority");
    }
    catch (const std::exception &exception) {
        Reader::HandleException(exception);
        return Factory::CreateState("priority");
    }
}