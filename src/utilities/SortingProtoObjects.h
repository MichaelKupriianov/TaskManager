#pragma once

#include <algorithm>
#include "Task.pb.h"
#include "TasksSortBy.h"
#include "AliasesProtoObjects.h"
#include "ComparisonProtoObjects.h"

namespace model {
void SortingTasksWithId(ManyTasksWithId&, TasksSortBy);
}