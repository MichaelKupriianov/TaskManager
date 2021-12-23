#include "Convert.h"

namespace ui::convert {

    std::optional<api::Task::Priority> StringToPriority(const std::string& priority) {
        if (priority == "high") return api::Task_Priority_HIGH;
        if (priority == "medium") return api::Task_Priority_MEDIUM;
        if (priority == "low") return api::Task_Priority_LOW;
        if (priority == "none" || priority.empty()) return api::Task_Priority_NONE;
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
            if (result < 0) return std::nullopt;
            return result;
        }
        catch (...) {
            return std::nullopt;
        }
    }

    std::optional<api::TasksSortBy> StringToSortBy(const std::string& sort) {
        if (sort == "id" || sort.empty()) return api::TasksSortBy::ID;
        if (sort == "date") return api::TasksSortBy::DATE;
        if (sort == "priority") return api::TasksSortBy::PRIORITY;
        return std::nullopt;
    }

    std::string PriorityToString(api::Task::Priority priority) {
        switch (priority) {
            case api::Task_Priority_HIGH:
                return "high";
            case api::Task_Priority_MEDIUM:
                return "medium";
            case api::Task_Priority_LOW:
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
                return "[Save]";
            case step::Type::LOAD:
                return "[Load]";
            default:
                assert(false);
        }
    }

    std::string TaskToString(const std::pair<api::TaskId, api::Task>& task) {
        std::string result;
        result += "id: " + std::to_string(task.first.value());
        result += ", title: " + task.second.title();
        result += ", priority: " + convert::PriorityToString(task.second.priority());
        result += ", date: " + convert::DateToString(task.second.date());
        if (!task.second.label().empty()) result += ", label: " + task.second.label();
        return result;
    }
}