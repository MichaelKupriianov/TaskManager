#pragma once

#include<memory>
#include"Task.pb.h"
#include"TaskId.pb.h"
#include"TaskManager.h"
#include"SortBy.h"
#include"View.h"

class Command {
public:
    virtual bool execute(const std::shared_ptr<TaskManager> &) = 0;

    virtual ~Command() = default;
};

class CommandQuit : public Command {
public:
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandQuit() = default;
};

class CommandAdd : public Command {
public:
    explicit CommandAdd(const Task &, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandAdd() = default;
private:
    const Task task_;
    const std::shared_ptr<View> view_;
};

class CommandAddSub : public Command {
public:
    explicit CommandAddSub(const Task &, TaskId, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandAddSub() = default;
private:
    const Task task_;
    const TaskId parent_id_;
    const std::shared_ptr<View> view_;
};

class CommandEdit : public Command {
public:
    explicit CommandEdit(TaskId, const Task &, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandEdit() = default;
private:
    const Task task_;
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandComplete : public Command {
public:
    explicit CommandComplete(TaskId, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandComplete() = default;
private:
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandDelete : public Command {
public:
    explicit CommandDelete(TaskId, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandDelete() = default;
private:
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandShow : public Command {
public:
    explicit CommandShow(bool, SortBy, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandShow() = default;
private:
    const std::shared_ptr<View> view_;
    const bool if_print_subtasks_;
    const SortBy sort_by_;
};

class CommandShowTask : public Command {
public:
    explicit CommandShowTask(TaskId, SortBy, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandShowTask() = default;
private:
    const std::shared_ptr<View> view_;
    const TaskId id_;
    const SortBy sort_by_;
};

class CommandShowLabel : public Command {
public:
    explicit CommandShowLabel(const std::string &, SortBy, const std::shared_ptr<View> &);
    virtual bool execute(const std::shared_ptr<TaskManager> &) override;
    virtual ~CommandShowLabel() = default;
private:
    const std::shared_ptr<View> view_;
    const std::string label_;
    const SortBy sort_by_;
};