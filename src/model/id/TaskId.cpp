#include "TaskId.h"

std::optional<TaskId> TaskId::Create(int id) {
    if (id < 0) return std::nullopt;
    return TaskId(static_cast<unsigned int>(id));
}

bool operator<(const TaskId &first, const TaskId &second) {
    return first.value() < second.value();
}

bool operator>(const TaskId &first, const TaskId &second) {
    return first.value() > second.value();
}

bool operator==(const TaskId &first, const TaskId &second) {
    return first.value() == second.value();
}