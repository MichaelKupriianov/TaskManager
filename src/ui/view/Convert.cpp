#include "Convert.h"

namespace convert {
    std::optional<Task::Priority> StringToPriority(const std::string &priority) {
        if (priority == "high") return Task_Priority_HIGH;
        if (priority == "medium") return Task_Priority_MEDIUM;
        if (priority == "low") return Task_Priority_LOW;
        if (priority == "none" || priority.empty()) return Task_Priority_NONE;
        return std::nullopt;
    }

    std::optional<time_t> StringToDate(const std::string &date) {
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

    std::optional<TypeOfStep> StringToStepType(const std::string &command) {
        if (command == "quit") return TypeOfStep::QUIT;
        if (command == "help") return TypeOfStep::HELP;
        if (command == "add") return TypeOfStep::ADD;
        if (command == "add_subtask") return TypeOfStep::ADD_SUB;
        if (command == "edit") return TypeOfStep::EDIT;
        if (command == "complete") return TypeOfStep::COMPLETE;
        if (command == "delete") return TypeOfStep::DELETE;
        if (command == "show") return TypeOfStep::SHOW;
        if (command == "show_task") return TypeOfStep::SHOW_TASK;
        if (command == "show_label") return TypeOfStep::SHOW_LABEL;
        if (command == "save") return TypeOfStep::SAVE;
        if (command == "load") return TypeOfStep::LOAD;
        return std::nullopt;
    }

    std::optional<int> StringToId(const std::string &id) {
        for (int i = 0; i < id.size(); i++)
            if (id[i] < '0' || id[i] > '9') return std::nullopt;
        try {
            int result = std::stoi(id);
            if (result < 0) return std::nullopt;
            return result;
        }
        catch (...) {
            return std::nullopt;
        }
    }

    std::optional<TasksSortBy> StringToSortBy(const std::string &sort) {
        if (sort == "id" || sort == "") return TasksSortBy::ID;
        if (sort == "date") return TasksSortBy::DATE;
        if (sort == "priority") return TasksSortBy::PRIORITY;
        return std::nullopt;
    }

    std::string PriorityToString(Task::Priority priority) {
        switch (priority) {
            case Task_Priority_HIGH:
                return "high";
            case Task_Priority_MEDIUM:
                return "medium";
            case Task_Priority_LOW:
                return "low";
            default:
                return "none";
        }
    }

    std::string DateToString(google::protobuf::Timestamp date) {
        if (date.seconds() == 0) return "none";
        time_t time{date.seconds()};
        std::string result = ctime(&time);
        for (int i = 0; i < 9; i++) result.pop_back();
        for (int i = 0; i < 4; i++) result.erase(result.begin());
        return result;
    }

    std::string CommandToString(TypeOfStep command) {
        switch (command) {
            case TypeOfStep::ADD:
                return "[Add Task]";
            case TypeOfStep::ADD_SUB:
                return "[Add SubTask]";
            case TypeOfStep::EDIT:
                return "[Edit Task]";
            case TypeOfStep::COMPLETE:
                return "[Complete Task]";
            case TypeOfStep::DELETE:
                return "[Delete Task]";
            case TypeOfStep::SHOW:
                return "[Show]";
            case TypeOfStep::SHOW_TASK:
                return "[Show Task]";
            case TypeOfStep::SHOW_LABEL:
                return "[Show by label]";
            case TypeOfStep::SAVE:
                return "[Save]";
            case TypeOfStep::LOAD:
                return "[Load]";
            default:
                assert(false);
        }
    }

    std::string TaskToString(const std::pair<TaskId, Task> &task) {
        std::string result = "";
        result += "id: " + std::to_string(task.first.value());
        result += ", title: " + task.second.title();
        result += ", priority: " + convert::PriorityToString(task.second.priority());
        result += ", date: " + convert::DateToString(task.second.date());
        if (!task.second.label().empty()) result += ", label: " + task.second.label();
        return result;
    }
}