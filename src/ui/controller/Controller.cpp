#include"Controller.h"
#include"Printer.h"

void Controller::Run() {
    while (true) {
        Context context{step_machine_.Run()};
        if (context.command() == Command::QUIT) break;
        Execute(context);
    }
}

void Controller::Execute(const Context & context) {
    switch (context.command()) {
        case Command::ADD:
            Add(context.task(), context.id());
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
            break;
        default:
            break;
    }
}

void Controller::Add(const Task &task, TaskId id) {
    if (!task_manager_.Add(task, id))
        Printer::PrintException("Incorrect parent ID (for example, subtask cannot have child)");
}

void Controller::Edit(TaskId id, const Task &task) {
    if (!task_manager_.Edit(id, task))
        Printer::PrintException("There are no task with such ID");
}

void Controller::Complete(TaskId id) {
    if (!task_manager_.Complete(id))
        Printer::PrintException("There are no task with such ID");
}

void Controller::Delete(TaskId id) {
    if (!task_manager_.Delete(id))
        Printer::PrintException("There are no task with such ID");
}

void Controller::Label(TaskId id, const std::string &label) {
    if (!task_manager_.Label(id, label))
        Printer::PrintException("There are no task with such ID");
}

void Controller::Show() {
    Printer::PrintAllTasks(task_manager_.ShowAll());
}