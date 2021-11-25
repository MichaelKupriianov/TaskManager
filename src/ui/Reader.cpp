#include "Reader.h"
#include<iostream>

void Reader::Help() {
    std::cout << "You can use such command:\n";
    std::cout << "add - Add new task\n";
    std::cout << "edit - Edit existent task\n";
    std::cout << "complete - Complete existent task\n";
    std::cout << "delete - Delete existent task\n";
    std::cout << "label - Edit label of existent task\n";
    std::cout << "show - Show all tasks\n";
    std::cout << "quit - finish work\n\n";
}

void Reader::Quit() {
    std::cout << "Good luck!\n";
}

std::string Reader::ReadCommand() {
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);
    return command;
}

int Reader::ReadId(const std::string &command) {
    std::cout << "[" << command << " Task] id: ";
    std::string id;
    getline(std::cin, id);
    try {
        return std::stoi(id);
    }
    catch (...) {
        std::cout << "This is not ID\n";
        return ReadId(command);
    }
}

std::string Reader::ReadTitle(const std::string &command) {
    std::cout << "[" << command << " Task] title: ";
    std::string title;
    getline(std::cin, title);
    return title;
}

std::string Reader::ReadPriority(const std::string &command) {
    std::cout << "[" << command << " Task] priority (high, medium, lou or none): ";
    std::string priority;
    getline(std::cin, priority);
    return priority;
}

std::string Reader::ReadTime(const std::string &command) {
    std::cout << "[" << command << " Task] time (in 12:12 12/12/2012 format): ";
    std::string time;
    getline(std::cin, time);
    return time;
}

std::string Reader::ReadLabel(const std::string &command) {
    std::cout << "[" << command << " Task] label: ";
    std::string label;
    getline(std::cin, label);
    return label;
}

bool Reader::Confirm() {
    std::cout << "Confirm? (Y/N): ";
    std::string answer;
    getline(std::cin, answer);
    if (answer == "Y") return true;
    if (answer == "N") return false;
    return Confirm();
}

void Reader::HandleException(const std::exception &exception) {
    std::cout << exception.what() << '\n';
}

time_t StringToTime(const std::string &date) {
    tm time = {};
    std::string pattern{"%H:%M %d/%m/%Y"};
    if (!strptime(date.c_str(), pattern.c_str(), &time))
        throw std::runtime_error("Incorrect time entry");
    return mktime(&time);
}

std::string TimeToString(time_t time) {
    return ctime(&time);
}