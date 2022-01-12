#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "utilities/AliasesProtoObjects.h"

class TaskPersister {
public:
    virtual bool Save(const model::ManyHierarchicalTasks& tasks, const std::string& filename);
    virtual std::optional<model::ManyHierarchicalTasks> Load(const std::string& filename);

    virtual ~TaskPersister() = default;
};


