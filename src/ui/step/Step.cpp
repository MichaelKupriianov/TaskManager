#include"Step.h"
#include<string>
#include<stdexcept>
#include"Factory.h"

std::unique_ptr<Step> StepCommand::execute(Context &context) {
    std::string command(reader.ReadCommand());
    try {
        return Factory::CreateStep(command);
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateStep("command");
    }
}

std::unique_ptr<Step> StepQuit::execute(Context &context) {
    reader.Quit();
    context.set_global_finished();
    return Factory::CreateStep("quit");
}

std::unique_ptr<Step> StepHelp::execute(Context &context) {
    reader.Help();
    return Factory::CreateStep("command");
}

std::unique_ptr<Step> StepComplete::execute(Context &context) {
    context.set_current_step("Complete");
    context.set_id(reader.ReadId(context.current_step()));
    if (!reader.Confirm()) {}
    return Factory::CreateStep("command");
}

std::unique_ptr<Step> StepDelete::execute(Context &context) {
    context.set_current_step("Delete");
    context.set_id(reader.ReadId(context.current_step()));
    if (!reader.Confirm()) {}
    return Factory::CreateStep("command");
}

std::unique_ptr<Step> StepLabel::execute(Context &context) {
    context.set_current_step("Label");
    context.set_task({context.task_title(), context.task_priority(), context.task_date(),
                      reader.ReadLabel(context.current_step()), context.task_state()});
    if (!reader.Confirm()) {}
    return Factory::CreateStep("command");
}

std::unique_ptr<Step> StepShow::execute(Context &context) {
    return Factory::CreateStep("command");
}