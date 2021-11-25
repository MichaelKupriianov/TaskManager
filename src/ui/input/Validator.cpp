#include "Validator.h"

std::optional<std::string> Validator::ValidateCommand(const std::string &command) {
    if (command == "help" || command == "quit" || command == "add" || command == "edit" || command == "complete" ||
        command == "delete" || command == "label" || command == "show")
        return std::nullopt;
    return "There is no such command\n";
}

std::optional<std::string> Validator::ValidateId(const std::string &str_id) {
    try {
        int id = std::stoi(str_id);
        if (id < 0) return "ID should be non-negative\n";
        return std::nullopt;
    }
    catch (...) {
        return "This is not ID\n";
    }
}

std::optional<std::string> Validator::ValidateTitle(const std::string &title) {
    if (title.empty()) return "There are no tasks without title\n";
    return std::nullopt;
}

std::optional<std::string> Validator::ValidatePriority(const std::string &priority) {
    if (priority == "high" || priority == "medium" || priority == "lou" || priority == "none") return std::nullopt;
    return "There is no such priority\n";
}

std::optional<std::string> Validator::ValidateTime(const std::string &str_time) {
    try {
        time_t time = StringToTime(str_time);
        if (time < 0) return "Time should be after January 1, 1970\n";
        return std::nullopt;
    }
    catch (...) {
        return "Enter the time in the correct format\n";
    }
}

std::optional<std::string> Validator::ValidateConfirm(const std::string &confirm) {
    if (confirm == "Y" || confirm == "N") return std::nullopt;
    return "error";
}


time_t StringToTime(const std::string &date) {
    tm time = {};
    std::string pattern{"%H:%M %d/%m/%Y"};
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        throw std::runtime_error("Incorrect time entry");
    return mktime(&time);
}