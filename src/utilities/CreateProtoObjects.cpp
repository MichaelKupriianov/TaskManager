#include "CreateProtoObjects.h"

namespace model {

TaskId CreateTaskId(int value) {
    TaskId id;
    id.set_value(value);
    return id;
}

Task CreateTask(const std::string& title, Task_Priority priority,
                time_t date, const std::vector<std::string>& labels, Task_Status status) {
    Task task;
    task.set_title(title);
    task.set_priority(priority);
    google::protobuf::Timestamp time;
    time.set_seconds(date);
    task.set_allocated_date(new google::protobuf::Timestamp(time));
    for(const auto& label: labels)
        task.add_labels(label);
    task.set_status(status);
    return task;
}

TaskWithId CreateTaskWithId(const TaskId& id, const Task& task) {
    TaskWithId task_with_id;
    task_with_id.set_allocated_task(new Task(task));
    task_with_id.set_allocated_id(new TaskId(id));
    return task_with_id;
}

TaskWithId CreateTaskWithId(const int& id, const std::string& task) {
    TaskWithId task_with_id;
    task_with_id.set_allocated_task(new Task(CreateTask(task)));
    task_with_id.set_allocated_id(new TaskId(CreateTaskId(id)));
    return task_with_id;
}

CompositeTask CreateCompositeTask(const TaskWithId& task, const ManyTasksWithId& child) {
    CompositeTask composite_task;
    composite_task.set_allocated_task(new TaskWithId(task));
    composite_task.mutable_children()->Add(child.tasks().begin(), child.tasks().end());
    return composite_task;
}

HierarchicalTask CreateHierarchicalTask(const Task& task, std::optional<TaskId> parent) {
    HierarchicalTask hierarchical_task;
    hierarchical_task.set_allocated_task(new Task(task));
    if (parent.has_value())
        hierarchical_task.set_allocated_parent(new TaskId(parent.value()));
    return hierarchical_task;
}
}