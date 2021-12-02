#include "SubContext.h"

void SubContext::set_task(const Task::Arguments &parameter) {
    auto ptr = std::make_unique<Task>(Task::Create(parameter).value());
    task_ = std::move(ptr);
}