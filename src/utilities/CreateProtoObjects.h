#pragma once

#include "Task.pb.h"

namespace model {
TaskId CreateTaskId(int value);

Task CreateTask(const std::string& title, Task_Priority = Task_Priority_NONE,
                time_t date = 0, const std::vector<std::string>& labels = {}, Task_Status = Task_Status_IN_PROGRESS);

HierarchicalTask CreateHierarchicalTask(const Task& task, std::optional<TaskId> id);
}