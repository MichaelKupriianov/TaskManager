#include "View.h"
#include "utilities/CreateProtoObjects.h"

namespace ui {

View::View(const std::shared_ptr<Reader>& reader, const std::shared_ptr<Printer>& printer)
        : reader_{reader}, printer_{printer} {}

void View::PrintHelp() {
    std::string output_string;
    output_string += "You can use such command:\n";
    output_string += "add - Add new task\n";
    output_string += "add_subtask - Add new subtask\n";
    output_string += "edit - Edit existent task\n";
    output_string += "complete - Complete existent task\n";
    output_string += "delete - Delete existent task\n";
    output_string += "show - Show all tasks\n";
    output_string += "show_task - Show task with its subtasks\n";
    output_string += "show_by_label - Show tasks with some specific label\n";
    output_string += "save - GetAllTasks introduced tasks to a file\n";
    output_string += "load - Overwrite tasks for a file\n";
    output_string += "quit - finish work\n\n";
    printer_->PrintString(output_string);
}

void View::PrintQuit() {
    printer_->PrintString("Good luck!\n");
}

step::Type View::ReadCommand() {
    printer_->PrintString("> ");
    std::string command{reader_->ReadString()};

    if (auto result{convert::StringToStepType(command)}; result.has_value())
        return result.value();

    printer_->PrintString("There is no such command\n");
    return ReadCommand();
}

model::TaskId View::ReadId(const std::string& command) {
    printer_->PrintString(command + " ID: ");
    std::string string_id{reader_->ReadString()};

    if (auto result{convert::StringToId(string_id)}; result.has_value())
        return model::CreateTaskId(result.value());

    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadId(command);
}

model::TaskId View::ReadParentId(const std::string& command) {
    printer_->PrintString(command + " Parent ID: ");
    std::string parent_id{reader_->ReadString()};

    if (auto result{convert::StringToId(parent_id)}; result.has_value())
        return model::CreateTaskId(result.value());

    printer_->PrintString("Enter the ID in the correct format\n");
    return ReadParentId(command);
}

std::string View::ReadTitle(const std::string& command) {
    printer_->PrintString(command + " title: ");
    std::string title{reader_->ReadString()};

    if (!title.empty())
        return title;

    printer_->PrintString("Title should be non-empty\n");
    return ReadTitle(command);
}

model::Task::Priority View::ReadPriority(const std::string& command) {
    printer_->PrintString(command + " priority (high, medium, low or none): ");
    std::string priority{reader_->ReadString()};

    if (auto result{convert::StringToPriority(priority)}; result.has_value())
        return result.value();

    printer_->PrintString("There is no such priority\n");
    return ReadPriority(command);
}

google::protobuf::Timestamp View::ReadDate(const std::string& command) {
    printer_->PrintString(command + " due date (in 12:12 12/12 or 12/12 format): ");
    std::string time{reader_->ReadString()};

    if (auto result{convert::StringToDate(time)}; result.has_value()) {
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

bool View::ReadIfPrintSubtasks(const std::string& command) {
    printer_->PrintString(command + " Print subtasks? (y/n): ");
    std::string answer{reader_->ReadString()};

    if (answer == "y" || answer.empty()) return true;
    if (answer == "n") return false;
    return ReadIfPrintSubtasks(command);
}

std::string View::ReadLabel(const std::string& command) {
    printer_->PrintString(command + " label: ");
    std::string label{reader_->ReadString()};

    if (!label.empty())
        return label;

    printer_->PrintString("Label should be non-empty\n");
    return ReadLabel(command);
}

model::TasksSortBy View::ReadSortBy(const std::string& command) {
    printer_->PrintString(command + " sort by? (id, date or priority): ");
    std::string answer{reader_->ReadString()};

    if (auto result{convert::StringToSortBy(answer)}; result.has_value())
        return result.value();

    return ReadSortBy(command);
}

std::string View::ReadFilename(const std::string& command) {
    printer_->PrintString(command + " filename: ");
    std::string filename{reader_->ReadString()};

    if (!filename.empty())
        return filename;

    printer_->PrintString("Filename should be non-empty\n");
    return ReadFilename(command);
}

void View::PrintManyTasksWithId(const model::ManyTasksWithId& tasks) {
    for (const auto& task: tasks.tasks())
        printer_->PrintString(convert::TaskToString(task) + '\n');
    if (tasks.empty())
        printer_->PrintString("There are no such tasks now.\n");
}

void View::PrintCompositeTask(const model::CompositeTask& task) {
    std::string result = convert::TaskToString(task.task());
    if (!task.children().empty())
        result += "  :";
    printer_->PrintString(result + '\n');

    for (const auto& subtask: task.children())
        printer_->PrintString("   " + convert::TaskToString(subtask) + '\n');
}

void View::PrintManyCompositeTasks(const model::ManyCompositeTasks& tasks) {
    for (const auto& task: tasks.tasks())
        PrintCompositeTask(task);
    if (tasks.tasks().empty())
        printer_->PrintString("There are no such tasks now.\n");
}

void View::PrintError(const command::Error& error) {
    printer_->PrintString(convert::ErrorToString(error) + '\n');
}
}