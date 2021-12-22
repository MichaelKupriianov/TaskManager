#include "Task.pb.h"

namespace api {
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayTasks = std::vector<IdWithTask>;
    using TaskWithSubtasks = std::pair<IdWithTask, ArrayTasks>;
    using AllTasks = std::vector<TaskWithSubtasks>;
    using ArrayFamilyTasks = std::vector<std::pair<TaskId, FamilyTask>>;
}