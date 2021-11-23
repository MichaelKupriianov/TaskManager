#include "State.h"
#include<string>
#include<stdexcept>
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<State> StateCommand::execute(Context &context) {
    std::string command(Reader::ReadCommand());
    try {
        return Factory::CreateState(command);
    }
    catch (const std::exception &exception) {
        Reader::HandleException(exception);
        return Factory::CreateState("command");
    }
}

std::unique_ptr<State> StateQuit::execute(Context &context) {
    Reader::Quit();
    context.setFinished();
    return Factory::CreateState("quit");
}

std::unique_ptr<State> StateHelp::execute(Context &context) {
    Reader::Help();
    return Factory::CreateState("command");
}
