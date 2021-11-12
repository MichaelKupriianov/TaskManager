#include "Task.h"
#include<stdexcept>

Task Task::Create(const std::string &title, Priority priority, time_t time) {
    if (title == "") throw std::runtime_error("There are no tasks without title");
    if (time < 0) throw std::runtime_error("Time should be positive");
    return Task(title, priority, time);
}