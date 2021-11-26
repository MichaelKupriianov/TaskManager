#pragma once

#include<string>
#include<ctime>
#include"Task.h"
#include"TypeOfStep.h"

class ConsoleManager {
public:
    explicit ConsoleManager(TypeOfStep);

    void Help() const;
    void Quit() const;
    TypeOfStep ReadCommand() const;
    int ReadId() const;
    std::string ReadTitle() const;
    Task::Priority ReadPriority() const;
    time_t ReadTime() const;
    std::string ReadLabel() const;
    bool Confirm() const;
private:
    const std::string command_;
};