#pragma once

#include <ctime>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "step/TypeOfStep.h"
#include "api/TasksSortBy.h"

namespace convert {
    std::optional<Task::Priority> StringToPriority(const std::string &);
    std::optional<time_t> StringToDate(const std::string &);
    std::optional<TypeOfStep> StringToStepType(const std::string &);
    std::optional<int> StringToId(const std::string &);
    std::optional<TasksSortBy> StringToSortBy(const std::string &);
    std::string PriorityToString(Task::Priority);
    std::string DateToString(google::protobuf::Timestamp date);
    std::string CommandToString(TypeOfStep command);
    std::string TaskToString(const std::pair<TaskId, Task> &task);
}

