#pragma once

#include<ctime>
#include<string>
#include<optional>
#include"Task.h"
#include"TypeOfStep.h"

class Converter {
public:
    static std::optional<Task::Priority> StringToPriority(const std::string &);
    static std::optional<time_t> StringToTime(const std::string &);
    static std::optional<TypeOfStep> StringToStepType(const std::string &);
    static std::optional<int> StringToId(const std::string &);
    static std::string PriorityToString(Task::Priority);
    static std::string StepTypeToString(TypeOfStep step);
};

