#pragma once

#include <ctime>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "ui/step/Type.h"
#include "api/TasksSortBy.h"

namespace ui::convert {
    std::optional<api::Task::Priority> StringToPriority(const std::string&);
    std::optional<time_t> StringToDate(const std::string&);
    std::optional<step::Type> StringToStepType(const std::string&);
    std::optional<int> StringToId(const std::string&);
    std::optional<api::TasksSortBy> StringToSortBy(const std::string&);
    std::string PriorityToString(api::Task::Priority);
    std::string DateToString(const google::protobuf::Timestamp& date);
    std::string CommandToString(step::Type command);
    std::string TaskToString(const std::pair<api::TaskId, api::Task>& task);
}

