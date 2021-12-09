#pragma once

#include<memory>
#include<string>
#include"Command.h"

class Context {
public:
    std::shared_ptr<Command> command() const { return command_; }

    void set_command(const std::shared_ptr<Command> &command) { command_ = command; }
private:
    std::shared_ptr<Command> command_ = nullptr;
};
