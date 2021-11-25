#include "input/ConsoleManager.h"
#include<iostream>
#include<optional>
#include"Validator.h"

void ConsoleManager::Help() {
    std::cout << "You can use such command:\n";
    std::cout << "add - Add new task\n";
    std::cout << "edit - Edit existent task\n";
    std::cout << "complete - Complete existent task\n";
    std::cout << "delete - Delete existent task\n";
    std::cout << "label - Edit label of existent task\n";
    std::cout << "show - Show all tasks\n";
    std::cout << "quit - finish work\n\n";
}

void ConsoleManager::Quit() {
    std::cout << "Good luck!\n";
}

std::string ConsoleManager::ReadCommand() {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    if (std::optional<std::string> error = Validator::ValidateCommand(command); error.has_value()) {
        std::cout << error.value();
        return ReadCommand();
    }
    return command;
}

int ConsoleManager::ReadId(const std::string &command) {
    std::cout << "[" << command << " Task] id: ";
    std::string id;
    getline(std::cin, id);
    if (std::optional<std::string> error = Validator::ValidateId(id); error.has_value()) {
        std::cout << error.value();
        return ReadId(command);
    }
    return std::stoi(id);
}

std::string ConsoleManager::ReadTitle(const std::string &command) {
    std::cout << "[" << command << " Task] title: ";
    std::string title;
    getline(std::cin, title);
    if (std::optional<std::string> error = Validator::ValidateTitle(title); error.has_value()) {
        std::cout << error.value();
        return ReadTitle(command);
    }
    return title;
}

Task::Priority ConsoleManager::ReadPriority(const std::string &command) {
    std::cout << "[" << command << " Task] priority (high, medium, lou or none): ";
    std::string priority;
    getline(std::cin, priority);
    if (std::optional<std::string> error = Validator::ValidatePriority(priority); error.has_value()) {
        std::cout << error.value();
        return ReadPriority(command);
    }
    return StringToPriority(priority);
}

time_t ConsoleManager::ReadTime(const std::string &command) {
    std::cout << "[" << command << " Task] time (in 12:12 12/12/2012 format): ";
    std::string time;
    getline(std::cin, time);
    if (std::optional<std::string> error = Validator::ValidateTime(time); error.has_value()) {
        std::cout << error.value();
        return ReadTime(command);
    }
    return StringToTime(time);
}

std::string ConsoleManager::ReadLabel(const std::string &command) {
    std::cout << "[" << command << " Task] label: ";
    std::string label;
    getline(std::cin, label);
    return label;
}

bool ConsoleManager::Confirm() {
    std::cout << "Confirm? (Y/N): ";
    std::string answer;
    getline(std::cin, answer);
    if (std::optional<std::string> error = Validator::ValidateConfirm(answer); error.has_value()) {
        return Confirm();
    }
    if (answer == "Y") return true;
    return false;
}


Task::Priority StringToPriority(const std::string &priority) {
    if (priority == "high") return Task::Priority::HIGH;
    if (priority == "medium") return Task::Priority::MEDIUM;
    if (priority == "lou") return Task::Priority::LOU;
    if (priority == "none") return Task::Priority::NONE;
    throw std::runtime_error("There is no such priority");
}

std::string PriorityToString(Task::Priority priority) {
    if (priority == Task::Priority::HIGH) return "high";
    if (priority == Task::Priority::MEDIUM) return "medium";
    if (priority == Task::Priority::LOU) return "lou";
    return "none";
}