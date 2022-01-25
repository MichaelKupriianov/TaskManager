#include "SortingProtoObjects.h"

namespace model {

bool ComparatorId(const model::TaskWithId& first, const model::TaskWithId& second) {
    return first.first < second.first;
}

bool ComparatorPriority(const model::TaskWithId& first, const model::TaskWithId& second) {
    return static_cast<int>(first.second.priority()) < static_cast<int>(second.second.priority());
}

bool ComparatorDate(const model::TaskWithId& first, const model::TaskWithId& second) {
    return first.second.date().seconds() < second.second.date().seconds();
}

void SortTasksWithId(ManyTasksWithId& tasks, const TasksSortBy& sort_by) {
    if (sort_by == TasksSortBy::ID)
        std::sort(tasks.begin(), tasks.end(), ComparatorId);
    if (sort_by == TasksSortBy::PRIORITY)
        std::sort(tasks.begin(), tasks.end(), ComparatorPriority);
    if (sort_by == TasksSortBy::DATE)
        std::sort(tasks.begin(), tasks.end(), ComparatorDate);
}
}