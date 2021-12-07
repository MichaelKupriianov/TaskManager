#include"Context.h"

void Context::set_id(int id) {
    if (id == -1) task_id_ = std::move(std::make_unique<TaskId>(TaskId::NotExistentId()));
    else task_id_ = std::move(std::make_unique<TaskId>(TaskId::Create(id).value()));
}

void Context::set_task(const Task &task) {
    auto ptr = std::make_unique<Task>(task);
    task_ = std::move(ptr);
}