#pragma once

#include <ctime>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "ui/step/Type.h"
#include "model/TasksSortBy.h"
#include "ui/command/Error.h"

namespace ui::convert {
    std::optional<proto::Task::Priority> StringToPriority(const std::string&);
    std::optional<time_t> StringToDate(const std::string&);
    std::optional<step::Type> StringToStepType(const std::string&);
    std::optional<int> StringToId(const std::string&);
    std::optional<model::TasksSortBy> StringToSortBy(const std::string&);
    std::string PriorityToString(proto::Task::Priority);
    std::string DateToString(const google::protobuf::Timestamp& date);
    std::string CommandToString(step::Type command);
    std::string TaskToString(const std::pair<proto::TaskId, proto::Task>& task);
    std::string ErrorToString(command::Error);
}

