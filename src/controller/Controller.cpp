#include"Controller.h"
#include"Printer.h"

void Controller::Run() {
    while (true) {
        Context context = step_machine_.Run();
        if (context.command() == Command::QUIT) break;
        Execute(context);
    }
}

void Controller::Execute(const Context & context) {
    switch (context.command()) {
        case Command::ADD:
            Add(context.task());
            break;
        case Command::EDIT:
            Edit(context.id(), context.task());
            break;
        case Command::COMPLETE:
            Complete(context.id());
            break;
        case Command::DELETE:
            Delete(context.id());
            break;
        case Command::LABEL:
            Label(context.id(), context.label());
            break;
        case Command::SHOW:
            Show();
    }
}

void Controller::Add(const Task &task) {
    task_manager_.Add(task);
}

void Controller::Edit(TaskId id, const Task &task) {
    task_manager_.Edit(id, task);
}

void Controller::Complete(TaskId id) {
    task_manager_.Complete(id);
}

void Controller::Delete(TaskId id) {
    task_manager_.Delete(id);
}

void Controller::Label(TaskId id, const std::string &label) {
    task_manager_.Label(id, label);
}

void Controller::Show() {
    Printer::PrintAllTasks(task_manager_.ShowAll());
}