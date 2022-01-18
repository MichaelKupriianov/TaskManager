#include "ComparisonProtoObjects.h"
#include <set>

namespace model {

bool operator<(const TaskId& first, const TaskId& second) {
    return first.value() < second.value();
}

bool operator==(const TaskId& first, const TaskId& second) {
    return first.value() == second.value();
}

bool operator==(const ::google::protobuf::RepeatedPtrField <std::string>& first,
                const ::google::protobuf::RepeatedPtrField <std::string>& second) {
    std::set<std::string> fi;
    std::set<std::string> se;
    for (const auto& label: first)
        fi.insert(label);
    for (const auto& label: second)
        se.insert(label);
    return fi == se;
}

bool operator==(const Task& first, const Task& second) {
    return first.title() == second.title() && first.priority() == second.priority() &&
           first.has_date() == second.has_date() && first.date().seconds() == second.date().seconds() &&
           first.labels() == second.labels() && first.status() == second.status();
}

bool operator==(const HierarchicalTask& first, const HierarchicalTask& second) {
    return first.has_task() && second.has_task() && first.task() == second.task() &&
           ((!first.has_parent() && !second.has_parent()) ||
            (first.has_parent() && second.has_parent() && first.parent() == second.parent()));
}
}