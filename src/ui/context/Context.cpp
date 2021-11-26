#include"Context.h"

void Context::set_id(int id) {
    auto ptr = std::make_unique<TaskId>(TaskId::Create(id));
    task_id_ = std::move(ptr);
}