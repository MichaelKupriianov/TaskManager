#pragma once

#include <string>
#include <optional>
#include <vector>
#include "Task.pb.h"
#include "api/AliasesProtoObjects.h"

namespace ui::command {
    struct Result {
    public:
        explicit Result(bool i_finished) : finished{i_finished} {}
        explicit Result(const std::string& i_exception) : exception{i_exception}, finished{false} {}
        explicit Result(const api::ArrayTasks& i_array) : array{i_array}, finished{false} {}
        explicit Result(const api::TaskWithSubtasks& i_task) : task{i_task}, finished{false} {}
        explicit Result(const api::AllTasks& i_all_tasks) : all_tasks{i_all_tasks}, finished{false} {}

        const bool finished;
        const std::optional<std::string> exception;
        const std::optional<api::ArrayTasks> array;
        const std::optional<api::TaskWithSubtasks> task;
        const std::optional<api::AllTasks> all_tasks;
    };
}