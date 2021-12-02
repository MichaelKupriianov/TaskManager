#pragma once

#include<memory>
#include<string>
#include"Task.h"
#include"TaskId.h"
#include"Command.h"

class Context {
public:
    Context() : command_(Command::NONE) {}
public:
    Command command() const { return command_; }
    TaskId id() const { return *task_id_; }
    std::string label() const { return label_; }
    Task task() const { return *task_; }

    void set_command(Command command) { command_ = command; }
    void set_id(int task_id);
    void set_label(const std::string &label) { label_ = label; }
    void set_task(const Task &task);
private:
    Command command_;
    std::unique_ptr<TaskId> task_id_;
    std::string label_;
    std::unique_ptr<Task> task_;
};
