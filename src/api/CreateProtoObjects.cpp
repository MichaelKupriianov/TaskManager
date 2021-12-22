#include "CreateProtoObjects.h"

namespace api {
    Task CreateTask(const std::string& title, Task_Priority priority,
                    time_t date, const std::string& label, Task_Status status) {
        Task task;
        task.set_title(title);
        task.set_priority(priority);
        google::protobuf::Timestamp time;
        time.set_seconds(date);
        task.set_allocated_date(new google::protobuf::Timestamp(time));
        task.set_label(label);
        task.set_status(status);
        return task;
    }

    FamilyTask CreateFamilyTask(const Task& task, std::optional<TaskId> parent) {
        FamilyTask generalized_task;
        generalized_task.set_allocated_task(new Task(task));
        if (parent.has_value())
            generalized_task.set_allocated_parent(new TaskId(parent.value()));
        return generalized_task;
    }

    TaskId CreateTaskId(int value) {
        TaskId id;
        id.set_value(value);
        return id;
    }
}