#pragma once

#include <string>
#include <optional>
#include <vector>
#include "Task.pb.h"
#include "Error.h"
#include "utilities/AliasesProtoObjects.h"

namespace ui::command {
struct Result {
public:
    explicit Result(bool i_finished) : finished{i_finished} {}
    explicit Result(Error i_error) : error{i_error}, finished{false} {}
    explicit Result(const model::ManyTasksWithId& i_array) : array{i_array}, finished{false} {}
    explicit Result(const model::CompositeTask& i_task) : task{i_task}, finished{false} {}
    explicit Result(const model::ManyCompositeTasks& i_all_tasks) : all_tasks{i_all_tasks}, finished{false} {}

    const bool finished;
    const std::optional<Error> error;
    const std::optional<model::ManyTasksWithId> array;
    const std::optional<model::CompositeTask> task;
    const std::optional<model::ManyCompositeTasks> all_tasks;
};
}