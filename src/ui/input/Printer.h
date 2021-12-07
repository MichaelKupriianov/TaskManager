#pragma once

#include<vector>
#include<utility>
#include"Task.h"
#include"TaskId.h"

class Printer {
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayOfIdWithTask = std::vector<IdWithTask>;
public:
    void PrintSomeTasks(const ArrayOfIdWithTask &, const std::string &);
    void PrintAllTasks(
            const std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> &);
    void PrintException(const std::string &exception);
private:
    static void PrintTask(const std::pair<TaskId, Task> &);
};
