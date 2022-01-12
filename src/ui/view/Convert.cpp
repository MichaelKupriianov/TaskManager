#include "Convert.h"
#include <cassert>

namespace ui::convert {

std::optional<model::Task::Priority> StringToPriority(const std::string& priority) {
    if (priority == "high") return model::Task_Priority_HIGH;
    if (priority == "medium") return model::Task_Priority_MEDIUM;
    if (priority == "low") return model::Task_Priority_LOW;
    if (priority == "none" || priority.empty()) return model::Task_Priority_NONE;
    return std::nullopt;
}

std::optional<time_t> StringToDate(const std::string& date) {
    if (date.empty())
        return 0;

    std::string pattern;
    if (date.size() > 5)
        pattern = "%H:%M %d/%m";
    else
        pattern = "%d/%m";

    tm time = {};
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        return std::nullopt;

    time.tm_year = 2021;
    tm first = {};
    first.tm_year = 2021;
    first.tm_mon = 2;
    first.tm_mday = 27;
    first.tm_hour = 3;
    time_t summer_time = mktime(&first);

    tm second = {};
    second.tm_year = 2021;
    second.tm_mon = 9;
    second.tm_mday = 30;
    second.tm_hour = 3;
    time_t winter_time = mktime(&second);

    time_t result = mktime(&time);
    if (result >= summer_time && result < winter_time) result -= 3600;
    return result;
}

std::optional<step::Type> StringToStepType(const std::string& command) {
    if (command == "quit") return step::Type::QUIT;
    if (command == "help") return step::Type::HELP;
    if (command == "add") return step::Type::ADD;
    if (command == "add_subtask") return step::Type::ADD_SUB;
    if (command == "edit") return step::Type::EDIT;
    if (command == "complete") return step::Type::COMPLETE;
    if (command == "delete") return step::Type::DELETE;
    if (command == "show") return step::Type::SHOW;
    if (command == "show_task") return step::Type::SHOW_TASK;
    if (command == "show_label") return step::Type::SHOW_LABEL;
    if (command == "save") return step::Type::SAVE;
    if (command == "load") return step::Type::LOAD;
    return std::nullopt;
}

std::optional<int> StringToId(const std::string& id) {
    for (auto symbol: id)
        if (symbol < '0' || symbol > '9') return std::nullopt;
    try {
        int result = std::stoi(id);
        return result;
    }
    catch (...) {
        return std::nullopt;
    }
}

std::optional<model::TasksSortBy> StringToSortBy(const std::string& sort) {
    if (sort == "id" || sort.empty()) return model::TasksSortBy::ID;
    if (sort == "date") return model::TasksSortBy::DATE;
    if (sort == "priority") return model::TasksSortBy::PRIORITY;
    return std::nullopt;
}

std::string PriorityToString(model::Task::Priority priority) {
    switch (priority) {
        case model::Task_Priority_HIGH:
            return "high";
        case model::Task_Priority_MEDIUM:
            return "medium";
        case model::Task_Priority_LOW:
            return "low";
        default:
            return "none";
    }
}

std::string DateToString(const google::protobuf::Timestamp& date) {
    if (date.seconds() == 0) return "none";
    time_t time{date.seconds()};
    std::string result = ctime(&time);
    for (int i = 0; i < 9; i++) result.pop_back();
    for (int i = 0; i < 4; i++) result.erase(result.begin());
    return result;
}

std::string CommandToString(step::Type command) {
    switch (command) {
        case step::Type::ADD:
            return "[Add Task]";
        case step::Type::ADD_SUB:
            return "[Add SubTask]";
        case step::Type::EDIT:
            return "[Edit Task]";
        case step::Type::COMPLETE:
            return "[Complete Task]";
        case step::Type::DELETE:
            return "[Delete Task]";
        case step::Type::SHOW:
            return "[Show]";
        case step::Type::SHOW_TASK:
            return "[Show Task]";
        case step::Type::SHOW_LABEL:
            return "[Show by label]";
        case step::Type::SAVE:
            return "[Save to file]";
        case step::Type::LOAD:
            return "[Load from file]";
        default:
            assert(false);
    }
}

std::string TaskToString(const model::TaskWithId& task) {
    std::string result;
    result += "id: " + std::to_string(task.first.value());
    result += ", title: " + task.second.title();
    result += ", priority: " + convert::PriorityToString(task.second.priority());
    result += ", date: " + convert::DateToString(task.second.date());
    if (!task.second.label().empty()) result += ", label: " + task.second.label();
    return result;
}

std::string ErrorToString(command::Error error) {
    if (error == command::Error::INCORRECT_PARENT_ID)
        return "Incorrect parent ID (for example, subtask cannot have child)";
    if (error == command::Error::NO_TASK_WITH_SUCH_ID)
        return "There are no task with such ID";
    if (error == command::Error::CANNOT_SAVE_TO_FILE)
        return "Cannot save to the specified file";
    if (error == command::Error::CANNOT_LOAD_FROM_FILE)
        return "Cannot load from the specified file";
    assert(false);
}
}