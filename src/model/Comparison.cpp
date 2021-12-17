#include "Comparison.h"

bool operator<(const TaskId &first, const TaskId &second) {
    return first.value() < second.value();
}

bool operator==(const TaskId &first, const TaskId &second) {
    return first.value() == second.value();
}

bool operator==(const Task &first, const Task &second) {
    return first.title() == second.title() && first.priority() == second.priority() &&
           first.has_date() == second.has_date() && first.date().seconds() == second.date().seconds() &&
           first.label() == second.label();
}