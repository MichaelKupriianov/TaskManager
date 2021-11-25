#pragma once

#include<string>
#include"Task.h"

class ConsoleManager {
public:
    void Help();
    void Quit();
    std::string ReadCommand();
    int ReadId(const std::string &);
    std::string ReadTitle(const std::string &);
    Task::Priority ReadPriority(const std::string &);
    time_t ReadTime(const std::string &);
    std::string ReadLabel(const std::string &);
    bool Confirm();
};

Task::Priority StringToPriority(const std::string &);
std::string PriorityToString(const Task::Priority);