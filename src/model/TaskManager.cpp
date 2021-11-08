#include<map>
#include<stdexcept>
#include"Task.h"
#include "TaskManager.h"

int TaskManager::Add(Task task) {
    tasks_[max_id_] = task;
    return max_id_++;
}

void TaskManager::Edit(int id, Task task) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    tasks_[id] = task;
}

void TaskManager::Complete(int id) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    tasks_.erase(id);
}

void TaskManager::Delete(int id) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    tasks_.erase(id);
}

std::map<int, Task> TaskManager::Show() {
    return tasks_;
}