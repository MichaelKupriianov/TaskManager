#pragma once

#include<ctime>
#include<string>
#include<optional>
#include"Task.h"
#include"TaskId.h"
#include"TypeOfStep.h"
#include"TypeOfCommand.h"
#include"SortBy.h"

class Converter {
public:
    static std::optional<Task::Priority> StringToPriority(const std::string &);
    static std::optional<time_t> StringToDate(const std::string &);
    static std::optional<TypeOfStep> StringToStepType(const std::string &);
    static std::optional<int> StringToId(const std::string &);
    static std::optional<SortBy> StringToSortBy(const std::string &);
    static std::string PriorityToString(Task::Priority);
    static std::string DateToString(time_t date);
    static std::string CommandToString(TypeOfCommand command);
    static std::string TaskToString(const std::pair<TaskId, Task> &task);
};

