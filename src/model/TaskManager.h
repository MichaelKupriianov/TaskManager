#pragma once

#include<map>
#include"Task.h"
#include"id/IdGenerator.h"
#include"id/TaskId.h"

class TaskManager {
public:
    TaskManager() {}
    TaskId Add(Task);
    void Edit(TaskId, Task);
    void Complete(TaskId);
    void Delete(TaskId);
    std::map<TaskId, Task> Show() const;
    Task getTask(TaskId) const;
private:
    std::map<TaskId, Task> tasks_;
    IdGenerator generator_;
};
