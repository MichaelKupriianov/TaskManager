#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "TaskStructures.pb.h"

using ManyHierarchicalTasks = std::vector<std::pair<model::TaskId, model::HierarchicalTask>>;

class TaskPersister {
public:
    TaskPersister(const std::string& filename) : filename_{filename} {}

    virtual bool Save(const ManyHierarchicalTasks& tasks);
    virtual std::optional<ManyHierarchicalTasks> Load();

    virtual ~TaskPersister() = default;
private:
    const std::string filename_;
};

