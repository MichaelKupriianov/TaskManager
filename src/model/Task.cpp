#include "Task.h"
#include<stdexcept>

Task Task::Create(const std::string& title, Priority priority, time_t time) {
    return Task(title, priority, time);
}