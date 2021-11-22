#include "State.h"

#include<iostream>
#include<stdexcept>
#include<memory>

#include"StateAdd.h"

std::unique_ptr<State> StringToCommand(const std::string &command) {
    if (command == "add") return std::unique_ptr<State>(new StateAdd);
    if (command == "quit") return std::unique_ptr<State>(new StateQuit);
    throw std::runtime_error("There is no such command");
}

std::unique_ptr<State> StateCommand::execute(Context &context) {
    std::cout << "> ";

    std::string command;
    std::cin >> command;

    try {
        return StringToCommand(command);
    }
    catch (const std::exception &exception) {
        std::cout << exception.what() << '\n';
        return std::unique_ptr<State>(new StateCommand);
    }
}

std::unique_ptr<State> StateQuit::execute(Context &context) {
    std::cout << "Good Luck!\n";
    context.Finished();
    return std::unique_ptr<State>(new StateQuit);
}
