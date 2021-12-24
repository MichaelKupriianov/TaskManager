#pragma once

#include "Task.pb.h"

namespace proto {
    bool operator<(const TaskId& first, const TaskId& second);

    bool operator==(const TaskId& first, const TaskId& second);

    bool operator==(const Task& first, const Task& second);

    bool operator==(const HierarchicalTask& first, const HierarchicalTask& second);
}