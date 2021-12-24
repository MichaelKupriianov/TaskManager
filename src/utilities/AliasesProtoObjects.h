#include "Task.pb.h"

namespace proto {
    using SimpleTask = std::pair<TaskId, Task>;
    using ArraySimpleTasks = std::vector<SimpleTask>;
    using CompositeTask = std::pair<SimpleTask, ArraySimpleTasks>;
    using ArrayCompositeTasks = std::vector<CompositeTask>;
    using ArrayHierarchicalTasks = std::vector<std::pair<TaskId, HierarchicalTask>>;
}