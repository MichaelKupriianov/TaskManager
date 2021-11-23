#include"Context.h"

void Context::setTask(const std::string &title, Task::Priority priority, time_t time,
                      const std::string &label, Task::State state) {
    auto ptr = std::make_unique<Task>(Task::Create(title, priority, time, label, state));
    task_ = std::move(ptr);
}