#include"View.h"

View::View(const std::shared_ptr<Reader> &reader, const std::shared_ptr<Printer> &printer)
        : reader_{reader}, printer_{printer} {}

void View::Help() {
    printer_->PrintString("You can use such command:\n");
    printer_->PrintString("add - Add new task\n");
    printer_->PrintString("add_subtask - Add new subtask\n");
    printer_->PrintString("edit - Edit existent task\n");
    printer_->PrintString("complete - Complete existent task\n");
    printer_->PrintString("delete - Delete existent task\n");
    printer_->PrintString("show - Show all tasks\n");
    printer_->PrintString("show_task - Show task with its subtasks\n");
    printer_->PrintString("show_label - Show task with some specific label\n");
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
    printer_->PrintString(Converter::CommandToString(command) +
                          " label (if there is no label, leave empty): ");
    std::string label{reader_->ReadString()};
    return label;
}

bool View::Confirm() {
    printer_->PrintString("Confirm? (y/n): ");
    std::string answer{reader_->ReadString()};
    if (answer == "y") return true;
    if (answer == "n") return false;
    return Confirm();
}

bool View::ReadIfPrintSubtasks(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) + " Print subtasks? (y/n): ");
    std::string answer{reader_->ReadString()};
    if (answer == "y") return true;
    if (answer == "n") return false;
    return ReadIfPrintSubtasks(command);
}

SortBy View::ReadSortBy(TypeOfCommand command) {
    printer_->PrintString(Converter::CommandToString(command) +
                          " sort by? (id, date or priority): ");
    std::string answer{reader_->ReadString()};
    if (std::optional<SortBy> result{Converter::StringToSortBy(answer)}; result.has_value())
        return result.value();
    return ReadSortBy(command);
}

void View::PrintArrayOfTasks(const ArrayTasks &tasks) {
    for (const auto &task: tasks) {
        std::string result = Converter::TaskToString(task) + '\n';
        printer_->PrintString(result);
    }
}

void View::PrintTaskWithSubtasks(const TaskWithSubtasks &task) {
    std::string result = Converter::TaskToString(task.first);
    if (task.second.empty()) result += "\n";
    else result += "  :\n";
    printer_->PrintString(result);
    for (const auto &subtask: task.second) {
        result = "   " + Converter::TaskToString(subtask) + '\n';
        printer_->PrintString(result);
    }
}

void View::PrintAllTasks(const std::vector<TaskWithSubtasks> &tasks) {
    if (tasks.empty()) {
        printer_->PrintString("There are no outstanding tasks now.\n");
        return;
    }
    for (const auto &[task, subtasks]: tasks) {
        if (!subtasks.empty())
            PrintTaskWithSubtasks({task, subtasks});
        else
            printer_->PrintString(Converter::TaskToString(task) + '\n');
    }
}

void View::PrintException(const std::string &exception) {
    printer_->PrintString(exception + '\n');
}