#pragma once

#include<string>
#include<ctime>
#include"Task.h"
#include"TypeOfStep.h"
#include"Command.h"

class Reader {
public:
    void Help() const;
    void Quit() const;
    TypeOfStep ReadCommand() const;
    int ReadId(Command) const;
    int ReadParentId(Command) const;
    std::string ReadTitle(Command) const;
    Task::Priority ReadPriority(Command) const;
    time_t ReadDate(Command) const;
    std::string ReadLabel(Command) const;
    bool Confirm() const;
};