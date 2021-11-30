#pragma once

#include<vector>
#include<utility>
#include"Task.h"
#include"id/TaskId.h"

class Printer {
public:
    static void PrintSomeTasks(const std::vector<std::pair<TaskId, Task>> &);
    static void PrintAllTasks(
            const std::vector<std::pair<std::pair<TaskId, Task>, std::vector<std::pair<TaskId, Task>>>> &);
private:
    static void PrintTask(const std::pair<TaskId, Task> &);
};
