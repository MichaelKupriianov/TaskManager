#pragma once

#include <vector>
#include <string>
#include <optional>
#include "Task.pb.h"
#include "api/AliasesProtoObjects.h"

class TaskPersister {
public:
    virtual bool Save(const api::ArrayFamilyTasks&, const std::string&);
    virtual std::optional<api::ArrayFamilyTasks> Load(const std::string&);

    virtual ~TaskPersister() = default;
};


