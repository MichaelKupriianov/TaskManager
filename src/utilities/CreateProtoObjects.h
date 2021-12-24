#pragma once

#include "Task.pb.h"

namespace proto {
    TaskId CreateTaskId(int value);

    Task CreateTask(const std::string&, Task_Priority = Task_Priority_NONE,
                    time_t = 0, const std::string& = "", Task_Status = Task_Status_IN_PROGRESS);

    HierarchicalTask CreateHierarchicalTask(const Task&, std::optional<TaskId>);
}