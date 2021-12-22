#pragma once

#include "Task.pb.h"

namespace api {
    bool operator<(const TaskId& first, const TaskId& second);

    bool operator==(const TaskId& first, const TaskId& second);

    bool operator==(const Task& first, const Task& second);

    bool operator==(const FamilyTask& first, const FamilyTask& second);
}