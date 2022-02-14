#pragma once

#include "Task.pb.h"
#include "TaskStructures.pb.h"
#include <oprional>

TaskId CreateTaskId(int value);

Task CreateTask(const std::string& title, Task_Priority = Task_Priority_NONE,
                time_t date = 0, const std::vector<std::string>& labels = {}, Task_Status = Task_Status_IN_PROGRESS);

TaskWithId CreateTaskWithId(const TaskId& id, const Task& task);

TaskWithId CreateTaskWithId(const int& id, const std::string& task);

CompositeTask CreateCompositeTask(const TaskWithId& task, const ManyTasksWithId& child);

HierarchicalTask CreateHierarchicalTask(const Task& task, std::optional<TaskId> id);