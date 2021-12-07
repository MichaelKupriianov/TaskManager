#pragma once

#include<memory>
#include"StepMachine.h"
#include"TaskManager.h"
#include"Printer.h"

class Controller {
public:
    Controller(std::shared_ptr<StepMachine> &, std::shared_ptr<TaskManager> &, std::shared_ptr<Printer> &);

    void Run();
private:
    void Execute(const Context &);
    void Add(const Task &, TaskId id);
    void Edit(TaskId id, const Task &task);
    void Complete(TaskId id);
    void Delete(TaskId id);
    void Label(TaskId id, const std::string &);
    void Show();
private:
    std::shared_ptr<StepMachine> step_machine_;
    std::shared_ptr<TaskManager> task_manager_;
    std::shared_ptr<Printer> printer_;
};
