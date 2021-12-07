#pragma once

#include"StepMachine.h"
#include"TaskManager.h"
#include"Command.h"
#include"Context.h"

class Controller {
public:
    void Run();
private:
    void Execute(const Context &);
    void Add(const Task &);
    void Edit(TaskId id, const Task &task);
    void Complete(TaskId id);
    void Delete(TaskId id);
    void Label(TaskId id, const std::string &);
    void Show();
private:
    StepMachine step_machine_;
    TaskManager task_manager_;
};
