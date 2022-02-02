#pragma once

#include <ctime>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "TaskStructures.pb.h"
#include "ui/step/Type.h"
#include "ui/command/Error.h"

namespace convert {
std::optional<Task::Priority> StringToPriority(const std::string&);
std::optional<time_t> StringToDate(const std::string&);
std::optional<ui::step::Type> StringToStepType(const std::string&);
std::optional<int> StringToId(const std::string&);
std::optional<TasksSortBy> StringToSortBy(const std::string&);
std::vector<std::string> StringToLabels(const std::string&);
std::string PriorityToString(Task::Priority);
std::string DateToString(const google::protobuf::Timestamp& date);
std::string TaskToString(const TaskWithId& task);
std::string ErrorToString(ui::command::Error);
}

