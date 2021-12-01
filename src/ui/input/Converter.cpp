#include "Converter.h"

std::optional<Task::Priority> Converter::StringToPriority(const std::string &priority) {
    if (priority == "high") return Task::Priority::HIGH;
    if (priority == "medium") return Task::Priority::MEDIUM;
    if (priority == "lou") return Task::Priority::LOU;
    if (priority == "none" || priority == "") return Task::Priority::NONE;
    return std::nullopt;
}

std::optional<time_t> Converter::StringToDate(const std::string &date) {
    if (date == "") return 0;
    tm time = {};
    std::string pattern;
    if (date.size() > 5) pattern = "%H:%M %d/%m";
    else pattern = "%d/%m";
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        return std::nullopt;
    time.tm_year = 2021;
    return mktime(&time);
}

std::optional<TypeOfStep> Converter::StringToStepType(const std::string &command) {
    if (command == "quit") return TypeOfStep::QUIT;
    if (command == "help") return TypeOfStep::HELP;
    if (command == "add") return TypeOfStep::ADD;
    if (command == "edit") return TypeOfStep::EDIT;
    if (command == "complete") return TypeOfStep::COMPLETE;
    if (command == "delete") return TypeOfStep::DELETE;
    if (command == "label") return TypeOfStep::LABEL;
    if (command == "show") return TypeOfStep::SHOW;
    return std::nullopt;
}

std::optional<int> Converter::StringToId(const std::string &id) {
    try {
        int result = std::stoi(id);
        if (result < 0) return std::nullopt;
        return result;
    }
    catch (...) {
        return std::nullopt;
    }
}

std::string Converter::PriorityToString(Task::Priority priority) {
    switch (priority) {
        case Task::Priority::HIGH:
            return "high";
        case Task::Priority::MEDIUM:
            return "medium";
        case Task::Priority::LOU:
            return "lou";
        default:
            return "none";
    }
}

std::string Converter::DateToString(time_t date) {
    if (date == 0) return "none";
    std::string result = ctime(&date);
    for (int i = 0; i < 9; i++) result.pop_back();
    for (int i = 0; i < 4; i++) result.erase(result.begin());
    return result;
}

std::string Converter::StepTypeToString(TypeOfStep step_type) {
    switch (step_type) {
        case TypeOfStep::ADD:
            return "Add";
        case TypeOfStep::EDIT:
            return "Edit";
        case TypeOfStep::COMPLETE:
            return "Complete";
        case TypeOfStep::DELETE:
            return "Delete";
        case TypeOfStep::LABEL:
            return "Label";
        default:
            return "";
    }
}