#include"Controller.h"
#include"Context.h"

Controller::Controller(std::shared_ptr<StepMachine> &machine, std::shared_ptr<TaskManager> &manager,
                       std::shared_ptr<Printer> &printer) :
                       step_machine_{machine}, task_manager_{manager}, printer_{printer} {}

void Controller::Run() {
    while (true) {
        Context context{step_machine_->Run()};
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
    if (!task_manager_->Add(task, id))
        printer_->PrintException("Incorrect parent ID (for example, subtask cannot have child)");
}

void Controller::Edit(TaskId id, const Task &task) {
    if (!task_manager_->Edit(id, task))
        printer_->PrintException("There are no task with such ID");
}

void Controller::Complete(TaskId id) {
    if (!task_manager_->Complete(id))
        printer_->PrintException("There are no task with such ID");
}

void Controller::Delete(TaskId id) {
    if (!task_manager_->Delete(id))
        printer_->PrintException("There are no task with such ID");
}

void Controller::Label(TaskId id, const std::string &label) {
    if (!task_manager_->Label(id, label))
        printer_->PrintException("There are no task with such ID");
}

void Controller::Show() {
    printer_->PrintAllTasks(task_manager_->ShowAll());
}