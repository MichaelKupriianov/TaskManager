#include"Context.h"

void Context::set_id(int id) {
    auto ptr = std::make_unique<TaskId>(TaskId::Create(id).value());
    task_id_ = std::move(ptr);
}

void Context::set_task(const Task &task) {
    auto ptr = std::make_unique<Task>(task);
    task_ = std::move(ptr);
}