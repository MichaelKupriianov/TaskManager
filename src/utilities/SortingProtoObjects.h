#pragma once

#include <algorithm>
#include "Task.pb.h"
#include "AliasesProtoObjects.h"
#include "ComparisonProtoObjects.h"

namespace model {
void SortTasksWithId(ManyTasksWithId&, const TasksSortBy&);
}