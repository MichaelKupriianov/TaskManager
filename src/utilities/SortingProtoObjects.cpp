#include "SortingProtoObjects.h"

namespace model {

bool ComparatorId(const model::TaskWithId& first, const model::TaskWithId& second) {
    if (first.first < second.first) return true;
    return false;
}

bool ComparatorPriority(const model::TaskWithId& first, const model::TaskWithId& second) {
    if (static_cast<int>(first.second.priority()) < static_cast<int>(second.second.priority())) return true;
    return false;
}

bool ComparatorDate(const model::TaskWithId& first, const model::TaskWithId& second) {
    if (first.second.date().seconds() < second.second.date().seconds()) return true;
    return false;
}

void SortingTasksWithId(ManyTasksWithId& tasks, TasksSortBy sort_by) {
    if (sort_by == TasksSortBy::ID)
        std::sort(tasks.begin(), tasks.end(), ComparatorId);
    if (sort_by == TasksSortBy::PRIORITY)
        std::sort(tasks.begin(), tasks.end(), ComparatorPriority);
    if (sort_by == TasksSortBy::DATE)
        std::sort(tasks.begin(), tasks.end(), ComparatorDate);
}
}