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
    context.setFinished();
    return Factory::CreateStep("quit");
}

std::unique_ptr<Step> StepHelp::execute(Context &context) {
    reader.Help();
    return Factory::CreateStep("command");
}
