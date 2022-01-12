#include "Task.pb.h"

namespace model {
using TaskWithId = std::pair<TaskId, Task>;
using ManyTasksWithId = std::vector<TaskWithId>;
using CompositeTask = std::pair<TaskWithId, ManyTasksWithId>;
using ManyCompositeTasks = std::vector<CompositeTask>;
using ManyHierarchicalTasks = std::vector<std::pair<TaskId, HierarchicalTask>>;
}