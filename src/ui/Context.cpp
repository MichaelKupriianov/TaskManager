#include"Context.h"

void Context::setTask(const Task::Parameter &parameter) {
    auto ptr = std::make_unique<Task>(Task::Create(parameter));
    task_ = std::move(ptr);
}