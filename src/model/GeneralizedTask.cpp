#include "GeneralizedTask.h"

GeneralizedTask GeneralizedTask::Create(const Task &task, TaskId id) {
    return GeneralizedTask(task, id);
}

bool operator==(const GeneralizedTask &first, const GeneralizedTask &second) {
    return first.task_ == second.task_ && first.parent_ == second.parent_;
}