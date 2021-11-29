#include"ConsoleManager.h"
#include<iostream>
#include<optional>
#include"Converter.h"

ConsoleManager::ConsoleManager(TypeOfStep step) :
        command_(Converter::StepTypeToString(step)) {}

void ConsoleManager::Help() const {
    std::cout << "You can use such command:\n";
    std::cout << "add - Add new task\n";
    std::cout << "edit - Edit existent task\n";
    std::cout << "complete - Complete existent task\n";
    std::cout << "delete - Delete existent task\n";
    std::cout << "label - Edit label of existent task\n";
    std::cout << "show - Show all tasks\n";
    std::cout << "quit - finish work\n\n";
}

void ConsoleManager::Quit() const {
    std::cout << "Good luck!\n";
}

TypeOfStep ConsoleManager::ReadCommand() const {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    if (std::optional<TypeOfStep> result = Converter::StringToStepType(command); result.has_value())
        return result.value();
    std::cout << "There is no such command\n";
    return ReadCommand();
}

int ConsoleManager::ReadId() const {
    std::cout << "[" << command_ << " Task] ID: ";
    std::string id;
    getline(std::cin, id);
    if (std::optional<int> result = Converter::StringToId(id); result.has_value())
        return result.value();
    std::cout << "Enter the ID in the correct format\n";
    return ReadId();
}

std::string ConsoleManager::ReadTitle() const {
    std::cout << "[" << command_ << " Task] title: ";
    std::string title;
    getline(std::cin, title);
    if (!title.empty()) return title;
    std::cout << "Title should be non-empty\n";
    return ReadTitle();
}

Task::Priority ConsoleManager::ReadPriority() const {
    std::cout << "[" << command_ << " Task] priority (high, medium, lou or none): ";
    std::string priority;
    getline(std::cin, priority);
    if (std::optional<Task::Priority> result = Converter::StringToPriority(priority); result.has_value())
        return result.value();
    std::cout << "There is no such priority\n";
    return ReadPriority();
}

time_t ConsoleManager::ReadTime() const {
    std::cout << "[" << command_ << " Task] time (in 12:12 12/12 or 12/12 format): ";
    std::string time;
    getline(std::cin, time);
    if (std::optional<time_t> result = Converter::StringToTime(time); result.has_value())
        return result.value();
    std::cout << "Enter the time in the correct format (or don't enter anything):\n";
    return ReadTime();
}

std::string ConsoleManager::ReadLabel() const {
    std::cout << "[" << command_ << " Task] label: ";
    std::string label;
    getline(std::cin, label);
    return label;
}

bool ConsoleManager::Confirm() const {
    std::cout << "Confirm? (Y/N): ";
    std::string answer;
    getline(std::cin, answer);
    if (answer == "Y") return true;
    if (answer == "N") return false;
    return Confirm();
}