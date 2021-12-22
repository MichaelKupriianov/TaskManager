#pragma once

#include "Task.pb.h"

Task CreateTask(const std::string &, Task_Priority = Task_Priority_NONE,
                time_t = 0, const std::string & = "", Task_Status = Task_Status_IN_PROGRESS);

FamilyTask CreateFamilyTask(const Task &, std::optional<TaskId>);

TaskId CreateTaskId(int value);