#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "utilities/AliasesProtoObjects.h"

class TaskPersister {
public:
    TaskPersister(const std::string &filename) : filename_{filename} {}

    virtual bool Save(const model::ManyHierarchicalTasks& tasks);
    virtual std::optional<model::ManyHierarchicalTasks> Load();

    virtual ~TaskPersister() = default;
private:
    const std::string filename_;
};


