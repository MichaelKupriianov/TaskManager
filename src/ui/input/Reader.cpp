#include"Reader.h"
#include<iostream>
#include<optional>
#include"Converter.h"

void Reader::Help() const {
    std::cout << "You can use such command:\n";
    std::cout << "add - Add new task\n";
    std::cout << "edit - Edit existent task\n";
    std::cout << "complete - Complete existent task\n";
    std::cout << "delete - Delete existent task\n";
    std::cout << "label - Edit label of existent task\n";
    std::cout << "show - Show all tasks\n";
    std::cout << "quit - finish work\n\n";
}

void Reader::Quit() const {
    std::cout << "Good luck!\n";
}

TypeOfStep Reader::ReadCommand() const {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    if (std::optional<TypeOfStep> result = Converter::StringToStepType(command); result.has_value())
        return result.value();
    std::cout << "There is no such command\n";
    return ReadCommand();
}

int Reader::ReadId(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] ID: ";
    std::string id;
    getline(std::cin, id);
    if (std::optional<int> result = Converter::StringToId(id); result.has_value())
        return result.value();
    std::cout << "Enter the ID in the correct format\n";
    return ReadId(command);
}

int Reader::ReadParentId(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] Parent ID (leave empty if task has no parent): ";
    std::string id;
    getline(std::cin, id);
    if (id.empty())
        return -1;
    if (std::optional<int> result = Converter::StringToId(id); result.has_value())
        return result.value();
    std::cout << "Enter the ID in the correct format\n";
    return ReadId(command);
}

std::string Reader::ReadTitle(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] title: ";
    std::string title;
    getline(std::cin, title);
    if (!title.empty()) return title;
    std::cout << "Title should be non-empty\n";
    return ReadTitle(command);
}

Task::Priority Reader::ReadPriority(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] priority (high, medium, lou or none): ";
    std::string priority;
    getline(std::cin, priority);
    if (std::optional<Task::Priority> result = Converter::StringToPriority(priority); result.has_value())
        return result.value();
    std::cout << "There is no such priority\n";
    return ReadPriority(command);
}

time_t Reader::ReadDate(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] due date (in 12:12 12/12 or 12/12 format): ";
    std::string date;
    getline(std::cin, date);
    if (std::optional<time_t> result = Converter::StringToDate(date); result.has_value())
        return result.value();
    std::cout << "Enter the date in the correct format (or don't enter anything):\n";
    return ReadDate(command);
}

std::string Reader::ReadLabel(Command command) const {
    std::cout << "[" << Converter::CommandToString(command) << " Task] label: ";
    std::string label;
    getline(std::cin, label);
    if (!label.empty()) return label;
    std::cout << "Label should be non-empty\n";
    return ReadLabel(command);
}

bool Reader::Confirm() const {
    std::cout << "Confirm? (y/n): ";
    std::string answer;
    getline(std::cin, answer);
    if (answer == "y") return true;
    if (answer == "n") return false;
    return Confirm();
}