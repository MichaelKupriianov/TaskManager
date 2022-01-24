#include "View.h"

namespace ui {

View::View(const std::shared_ptr<Reader>& reader, const std::shared_ptr<Printer>& printer)
        : reader_{reader}, printer_{printer} {}

void View::PrintHelp() {
    printer_->PrintString("You can use such command:\n");
    printer_->PrintString("add - Add new task\n");
    printer_->PrintString("add_subtask - Add new subtask\n");
    printer_->PrintString("edit - Edit existent task\n");
    printer_->PrintString("complete - Complete existent task\n");
    printer_->PrintString("delete - Delete existent task\n");
    printer_->PrintString("show - Show all tasks\n");
    printer_->PrintString("show_task - Show task with its subtasks\n");
    printer_->PrintString("show_by_label - Show tasks with some specific label\n");
    printer_->PrintString("save - GetAllTasks introduced tasks to a file\n");
    printer_->PrintString("load - Overwrite tasks for a file\n");
    printer_->PrintString("quit - finish work\n\n");
}

void View::PrintQuit() {
    printer_->PrintString("Good luck!\n");
}

step::Type View::ReadCommand() {
    printer_->PrintString("> ");
    std::string command{reader_->ReadString()};

    if (std::optional<step::Type> result{convert::StringToStepType(command)}; result.has_value())
        return result.value();
    printer_->PrintString("There is no such command\n");
    return ReadCommand();
}

model::TaskId View::ReadId(const std::string &command) {
    printer_->PrintString(command + " ID: ");
    std::string string_id{reader_->ReadString()};

    if (std::optional<int> result{convert::StringToId(string_id)}; result.has_value()) {
        model::TaskId id;
        id.set_value(result.value());
        return id;
    }
    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadId(command);
}

model::TaskId View::ReadParentId(const std::string &command) {
    printer_->PrintString(command + " Parent ID: ");
    std::string parent_id{reader_->ReadString()};

    if (std::optional<int> result{convert::StringToId(parent_id)}; result.has_value()) {
        model::TaskId id;
        id.set_value(result.value());
        return id;
    }
    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadId(command);
}

std::string View::ReadTitle(const std::string &command) {
    printer_->PrintString(command + " title: ");
    std::string title{reader_->ReadString()};

    if (!title.empty()) return title;
    printer_->PrintString("Title should be non-empty\n");
    return ReadTitle(command);
}

model::Task::Priority View::ReadPriority(const std::string &command) {
    printer_->PrintString(command + " priority (high, medium, low or none): ");
    std::string priority{reader_->ReadString()};

    if (std::optional<model::Task::Priority> result{convert::StringToPriority(priority)}; result.has_value())
        return result.value();
    printer_->PrintString("There is no such priority\n");
    return ReadPriority(command);
}

google::protobuf::Timestamp View::ReadDate(const std::string &command) {
    printer_->PrintString(command + " due date (in 12:12 12/12 or 12/12 format): ");
    std::string string_date{reader_->ReadString()};

    if (std::optional<time_t> result{convert::StringToDate(string_date)}; result.has_value()) {
        google::protobuf::Timestamp date;
        date.set_seconds(result.value());
        return date;
    }
    printer_->PrintString("Enter the date in the correct format (or don't enter anything):\n");
    return ReadDate(command);
}

std::vector<std::string> View::ReadLabels(const std::string& command) {
    printer_->PrintString(command + " labels through a space (if there is no label, leave empty): ");
    std::string labels{reader_->ReadString()};
    return convert::StringToLabels(labels);
}

bool View::Confirm() {
    printer_->PrintString("Confirm? (y/n): ");
    std::string answer{reader_->ReadString()};

    if (answer == "y") return true;
    if (answer == "n") return false;
    return Confirm();
}

bool View::ReadIfPrintSubtasks(const std::string &command) {
    printer_->PrintString(command + " Print subtasks? (y/n): ");
    std::string answer{reader_->ReadString()};

    if (answer == "y") return true;
    if (answer == "n") return false;
    return ReadIfPrintSubtasks(command);
}

std::string View::ReadLabel(const std::string &command) {
    printer_->PrintString(command + " label: ");
    std::string label{reader_->ReadString()};
    return label;
}

model::TasksSortBy View::ReadSortBy(const std::string& command) {
    printer_->PrintString(command + " sort by? (id, date or priority): ");
    std::string answer{reader_->ReadString()};

    if (std::optional<model::TasksSortBy> result{convert::StringToSortBy(answer)}; result.has_value())
        return result.value();
    return ReadSortBy(command);
}

std::string View::ReadFilename(const std::string &command) {
    printer_->PrintString(command + " filename: ");
    std::string title{reader_->ReadString()};

    if (!title.empty()) return title;
    printer_->PrintString("Filename should be non-empty\n");
    return ReadTitle(command);
}

void View::PrintManyTasksWithId(const model::ManyTasksWithId& tasks) {
    for (const auto& task: tasks) {
        std::string result = convert::TaskToString(task) + '\n';
        printer_->PrintString(result);
    }
}

void View::PrintCompositeTask(const model::CompositeTask& task) {
    std::string result = convert::TaskToString(task.first);
    if (task.second.empty())
        result += "\n";
    else
        result += "  :\n";

    printer_->PrintString(result);
    for (const auto& subtask: task.second) {
        result = "   " + convert::TaskToString(subtask) + '\n';
        printer_->PrintString(result);
    }
}

void View::PrintManyCompositeTasks(const model::ManyCompositeTasks& tasks) {
    if (tasks.empty()) {
        printer_->PrintString("There are no outstanding tasks now.\n");
        return;
    }
    for (const auto &[task, subtasks]: tasks) {
        if (!subtasks.empty())
            PrintCompositeTask({task, subtasks});
        else
            printer_->PrintString(convert::TaskToString(task) + '\n');
    }
}

void View::PrintError(command::Error error) {
    printer_->PrintString(convert::ErrorToString(error) + '\n');
}
}