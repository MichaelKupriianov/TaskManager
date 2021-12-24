#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "utilities/AliasesProtoObjects.h"

class TaskPersister {
public:
    virtual bool Save(const proto::ArrayHierarchicalTasks&, const std::string&);
    virtual std::optional<proto::ArrayHierarchicalTasks> Load(const std::string&);

    virtual ~TaskPersister() = default;
};


