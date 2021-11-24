#include "State.h"
#include<string>
#include<stdexcept>
#include"Factory.h"

std::unique_ptr<State> StateCommand::execute(Context &context) {
    std::string command(reader.ReadCommand());
    try {
        return Factory::CreateState(command);
    }
    catch (const std::exception &exception) {
        reader.HandleException(exception);
        return Factory::CreateState("command");
    }
}

std::unique_ptr<State> StateQuit::execute(Context &context) {
    reader.Quit();
    context.setFinished();
    return Factory::CreateState("quit");
}

std::unique_ptr<State> StateHelp::execute(Context &context) {
    reader.Help();
    return Factory::CreateState("command");
}
