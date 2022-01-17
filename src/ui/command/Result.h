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
    explicit Result(const model::ManyTasksWithId& tasks) : many_tasks{tasks}, finished{false} {}
    explicit Result(const model::CompositeTask& task) : composite_task{task}, finished{false} {}
    explicit Result(const model::ManyCompositeTasks& tasks) : many_composite_tasks{tasks}, finished{false} {}

    bool has_value() {
        return error.has_value() || many_tasks.has_value() || composite_task.has_value() ||
               many_composite_tasks.has_value();
    }

    const bool finished;
    const std::optional<Error> error;
    const std::optional<model::ManyTasksWithId> many_tasks;
    const std::optional<model::CompositeTask> composite_task;
    const std::optional<model::ManyCompositeTasks> many_composite_tasks;
};
}