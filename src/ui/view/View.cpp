#include"View.h"
#include<optional>
#include"Converter.h"

View::View(const std::shared_ptr<Reader> &reader, const std::shared_ptr<Printer> &printer)
        : reader_{reader}, printer_{printer} {}

void View::Help() {
    printer_->PrintString("You can use such command:\n");
    printer_->PrintString("add - Add new task\n");
    printer_->PrintString("add subtask - Add new subtask\n");
    printer_->PrintString("edit - Edit existent task\n");
    printer_->PrintString("complete - Complete existent task\n");
    printer_->PrintString("delete - Delete existent task\n");
    printer_->PrintString("label - Edit label of existent task\n");
    printer_->PrintString("show - Show all tasks\n");
    printer_->PrintString("quit - finish work\n\n");
}

void View::Quit() {
    printer_->PrintString("Good luck!\n");
}

TypeOfStep View::ReadCommand() {
    printer_->PrintString("> ");
    std::string command{reader_->ReadString()};
    if (std::optional<TypeOfStep> result{Converter::StringToStepType(command)}; result.has_value())
        return result.value();
    printer_->PrintString("There is no such command\n");
    return ReadCommand();
}

TaskId View::ReadId(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " ID: ");
    std::string id{reader_->ReadString()};
    if (std::optional<int> result{Converter::StringToId(id)}; result.has_value())
        return TaskId::Create(result.value()).value();
    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadId(command);
}

TaskId View::ReadParentId(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " Parent ID: ");
    std::string id{reader_->ReadString()};
    if (std::optional<int> result{Converter::StringToId(id)}; result.has_value())
        return TaskId::Create(result.value()).value();
    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadId(command);
}

std::string View::ReadTitle(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " title: ");
    std::string title{reader_->ReadString()};
    if (!title.empty()) return title;
    printer_->PrintString("Title should be non-empty\n");
    return ReadTitle(command);
}

Task::Priority View::ReadPriority(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " priority (high, medium, lou or none): ");
    std::string priority{reader_->ReadString()};
    if (std::optional<Task::Priority> result{Converter::StringToPriority(priority)}; result.has_value())
        return result.value();
    printer_->PrintString("There is no such priority\n");
    return ReadPriority(command);
}

time_t View::ReadDate(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) +
                          " due date (in 12:12 12/12 or 12/12 format): ");
    std::string date{reader_->ReadString()};
    if (std::optional<time_t> result{Converter::StringToDate(date)}; result.has_value())
        return result.value();
    printer_->PrintString("Enter the date in the correct format (or don't enter anything):\n");
    return ReadDate(command);
}

std::string View::ReadLabel(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " label: ");
    std::string label{reader_->ReadString()};
    if (!label.empty()) return label;
    printer_->PrintString("Label should be non-empty\n");
    return ReadLabel(command);
}

bool View::Confirm() {
    printer_->PrintString("Confirm? (y/n): ");
    std::string answer{reader_->ReadString()};
    if (answer == "y") return true;
    if (answer == "n") return false;
    return Confirm();
}

void View::PrintSomeTasks(const ArrayOfIdWithTask &tasks, const std::string &introduction) {
    for (const auto &task: tasks) {
        printer_->PrintString(introduction);
        PrintTask(task);
        printer_->PrintString("\n");
    }
}

void View::PrintAllTasks(
        const std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> &tasks) {
    if (tasks.empty()) {
        printer_->PrintString("There are no outstanding tasks now.\n");
        return;
    }
    for (const auto &[task, children]: tasks) {
        PrintTask(task);
        if (!children.empty()) {
            printer_->PrintString("  :\n");
            PrintSomeTasks(children, "   ");
        } else printer_->PrintString("\n");
    }
}

void View::PrintException(const std::string &exception) {
    printer_->PrintString(exception + '\n');
}

void View::PrintTask(const std::pair<TaskId, Task> &task) {
    printer_->PrintString("id: " + std::to_string(task.first.value()));
    printer_->PrintString(", title: " + task.second.title());
    printer_->PrintString(", priority: " + Converter::PriorityToString(task.second.priority()));
    printer_->PrintString(", date: " + Converter::DateToString(task.second.date()));
    if (!task.second.label().empty()) printer_->PrintString(", label: " + task.second.label());
}
