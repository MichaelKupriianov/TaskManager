#pragma once

#include <memory>
#include "Task.pb.h"
#include "Dependency.h"
#include "Result.h"
#include "api/TasksSortBy.h"

namespace ui::command {

    class Command {
    public:
        virtual Result execute(const std::shared_ptr<Dependency>&) = 0;
        virtual ~Command() = default;
    };

    class Quit : public Command {
    public:
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Quit() override = default;
    };

    class Add : public Command {
    public:
        explicit Add(const api::Task&);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Add() override = default;
    private:
        const api::Task task_;
    };

    class AddSub : public Command {
    public:
        explicit AddSub(const api::Task&, api::TaskId);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~AddSub() override = default;
    private:
        const api::Task task_;
        const api::TaskId parent_id_;
    };

    class Edit : public Command {
    public:
        explicit Edit(api::TaskId, const api::Task&);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Edit() override = default;
    private:
        const api::TaskId id_;
        const api::Task task_;
    };

    class Complete : public Command {
    public:
        explicit Complete(api::TaskId);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Complete() override = default;
    private:
        const api::TaskId id_;
    };

    class Delete : public Command {
    public:
        explicit Delete(api::TaskId);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Delete() override = default;
    private:
        const api::TaskId id_;
    };

    class Show : public Command {
    public:
        explicit Show(bool, api::TasksSortBy);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Show() override = default;
    private:
        const bool if_print_subtasks_;
        const api::TasksSortBy sort_by_;
    };

    class ShowTask : public Command {
    public:
        explicit ShowTask(api::TaskId, api::TasksSortBy);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~ShowTask() override = default;
    private:
        const api::TaskId id_;
        const api::TasksSortBy sort_by_;
    };

    class ShowLabel : public Command {
    public:
        explicit ShowLabel(const std::string&, api::TasksSortBy);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~ShowLabel() override = default;
    private:
        const std::string label_;
        const api::TasksSortBy sort_by_;
    };

    class Save : public Command {
    public:
        explicit Save(const std::string&);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Save() override = default;
    private:
        const std::string filename_;
    };

    class Load : public Command {
    public:
        explicit Load(const std::string&);
        Result execute(const std::shared_ptr<Dependency>&) override;
        ~Load() override = default;
    private:
        const std::string filename_;
    };
}