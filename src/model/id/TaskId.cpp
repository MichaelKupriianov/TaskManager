#include "TaskId.h"
#include<stdexcept>

TaskId TaskId::Create(int id) {
    if (id < 0) throw std::range_error("Impossible to use negative ID");
    return TaskId(static_cast<unsigned int>(id));
};

bool operator<(const TaskId &first, const TaskId &second) {
    return first.value() < second.value();
}

bool operator==(const TaskId &first, const TaskId &second) {
    return first.value() == second.value();
}