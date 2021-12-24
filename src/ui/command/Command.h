#pragma once

#include <memory>
#include "Task.pb.h"
#include "Resources.h"
#include "Result.h"
#include "Error.h"
#include "model/TasksSortBy.h"

namespace ui::command {

    class Command {
    public:
        virtual Result execute(const std::shared_ptr<Resources>&) = 0;
        virtual ~Command() = default;
    };

    class Quit : public Command {
    public:
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Quit() override = default;
    };

    class Add : public Command {
    public:
        explicit Add(const proto::Task&);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Add() override = default;
    private:
        const proto::Task task_;
    };

    class AddSub : public Command {
    public:
        explicit AddSub(const proto::Task&, proto::TaskId);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~AddSub() override = default;
    private:
        const proto::Task task_;
        const proto::TaskId parent_id_;
    };

    class Edit : public Command {
    public:
        explicit Edit(proto::TaskId, const proto::Task&);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Edit() override = default;
    private:
        const proto::TaskId id_;
        const proto::Task task_;
    };

    class Complete : public Command {
    public:
        explicit Complete(proto::TaskId);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Complete() override = default;
    private:
        const proto::TaskId id_;
    };

    class Delete : public Command {
    public:
        explicit Delete(proto::TaskId);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Delete() override = default;
    private:
        const proto::TaskId id_;
    };

    class Show : public Command {
    public:
        explicit Show(bool, model::TasksSortBy);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Show() override = default;
    private:
        const bool if_print_subtasks_;
        const model::TasksSortBy sort_by_;
    };

    class ShowTask : public Command {
    public:
        explicit ShowTask(proto::TaskId, model::TasksSortBy);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~ShowTask() override = default;
    private:
        const proto::TaskId id_;
        const model::TasksSortBy sort_by_;
    };

    class ShowLabel : public Command {
    public:
        explicit ShowLabel(const std::string&, model::TasksSortBy);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~ShowLabel() override = default;
    private:
        const std::string label_;
        const model::TasksSortBy sort_by_;
    };

    class Save : public Command {
    public:
        explicit Save(const std::string&);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Save() override = default;
    private:
        const std::string filename_;
    };

    class Load : public Command {
    public:
        explicit Load(const std::string&);
        Result execute(const std::shared_ptr<Resources>&) override;
        ~Load() override = default;
    private:
        const std::string filename_;
    };
}