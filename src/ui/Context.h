#pragma once

#include <memory>
#include <optional>
#include "Task.pb.h"
#include "command/Command.h"
#include "command/Result.h"

namespace ui {

class Context {
public:
    explicit Context(const std::shared_ptr<command::Result>& result) : result_{result} {}
    explicit Context(const std::string& name) : command_name_{name}, task_{new model::Task} {}

    std::shared_ptr<command::Command> command() const { return command_; }
    std::shared_ptr<command::Result> result() const { return result_; }
    std::shared_ptr<model::Task> task() const { return task_; }
    std::string command_name() const { return command_name_; }
    bool if_finished() const { return finished_; }

    void set_command(const std::shared_ptr<command::Command>& command) {
        command_ = command;
        finished_ = true;
    }
    void set_result() { result_ = std::make_shared<command::Result>(false); }
    void finished() { finished_ = true; }
private:
    std::shared_ptr<command::Command> command_;
    std::shared_ptr<command::Result> result_;
    std::shared_ptr<model::Task> task_;
    std::string command_name_;
    bool finished_ = false;
};
}