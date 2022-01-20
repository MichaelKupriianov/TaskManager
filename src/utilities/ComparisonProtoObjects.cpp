#include "ComparisonProtoObjects.h"

namespace model {

bool operator<(const TaskId& first, const TaskId& second) {
    return first.value() < second.value();
}

bool operator==(const TaskId& first, const TaskId& second) {
    return first.value() == second.value();
}

bool operator==(const Task& first, const Task& second) {
    return first.title() == second.title() && first.priority() == second.priority() &&
           first.has_date() == second.has_date() && first.date().seconds() == second.date().seconds() &&
           first.status() == second.status() && first.labels().size() == second.labels().size() &&
           std::equal(first.labels().begin(), first.labels().end(), second.labels().begin());
}

bool operator==(const HierarchicalTask& first, const HierarchicalTask& second) {
    return first.has_task() && second.has_task() && first.task() == second.task() &&
           ((!first.has_parent() && !second.has_parent()) ||
            (first.has_parent() && second.has_parent() && first.parent() == second.parent()));
}
}