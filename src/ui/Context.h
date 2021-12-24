#pragma once

#include <memory>
#include <optional>
#include "Task.pb.h"
#include "command/Command.h"
#include "command/Result.h"

namespace ui {

    class Context {
    public:
        bool has_command() const { return command_.has_value(); }
        bool has_result() const { return result_.has_value(); }

        std::shared_ptr<command::Command> command() const { return command_.value(); }
        std::shared_ptr<command::Result> result() const { return result_.value(); }

        void set_command(const std::shared_ptr<command::Command>& command) { command_ = command; }
        void set_result(const std::shared_ptr<command::Result>& result) { result_ = result; }
        void set_command(std::nullopt_t) { command_ = std::nullopt; }
        void set_result(std::nullopt_t) { result_ = std::nullopt; }
    private:
        std::optional<std::shared_ptr<command::Command>> command_;
        std::optional<std::shared_ptr<command::Result>> result_;
    };

    class SubContext {
    public:
        SubContext() : task_{new proto::Task} {}

        bool if_finished() const { return finished_; }
        std::shared_ptr<proto::Task> task() const { return task_; }

        void finished() { finished_ = true; }
    private:
        bool finished_ = false;
        std::shared_ptr<proto::Task> task_;
    };
}