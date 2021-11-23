#include "Reader.h"
#include<iostream>

void Reader::Help() {
    std::cout << "You can use such command:\n";
    std::cout << "add - Add new task\n";
    std::cout << "edit [Task ID] - Edit existent task\n";
    std::cout << "complete [Task ID] - Complete existent task\n";
    std::cout << "delete [Task ID]- Delete existent task\n";
    std::cout << "label [Task ID] - Edit label of existent task\n";
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
    std::cout << "[" << command << " Task] time (in 24:00 10/10/2000 format): ";
    std::string time;
    getline(std::cin, time);
    return time;
}

bool Reader::Confirm() {
    std::cout << "Confirm? (Y/N): ";
    std::string answer;
    getline(std::cin, answer);
    if (answer == "Y") return true;
    if (answer == "N") return false;
    return Reader::Confirm();
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