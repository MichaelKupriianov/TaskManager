#pragma once

#include<memory>
#include"Task.h"
#include"TaskId.h"
#include"TaskManager.h"
#include"View.h"

class Command {
public:
    virtual bool execute(const std::shared_ptr<TaskManager> &) = 0;

    virtual ~Command() = default;
};

class CommandAdd : public Command {
public:
    explicit CommandAdd(const Task &, const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const Task task_;
    const std::shared_ptr<View> view_;
};

class CommandAddSub : public Command {
public:
    explicit CommandAddSub(const Task &, TaskId, const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const Task task_;
    const TaskId parent_id_;
    const std::shared_ptr<View> view_;
};

class CommandEdit : public Command {
public:
    explicit CommandEdit(TaskId, const Task &, const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const Task task_;
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandComplete : public Command {
public:
    explicit CommandComplete(TaskId, const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandDelete : public Command {
public:
    explicit CommandDelete(TaskId, const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const TaskId id_;
    const std::shared_ptr<View> view_;
};

class CommandShow : public Command {
public:
    explicit CommandShow(const std::shared_ptr<View> &);
    bool execute(const std::shared_ptr<TaskManager> &) override;
private:
    const std::shared_ptr<View> view_;
};

class CommandQuit : public Command {
public:
    bool execute(const std::shared_ptr<TaskManager> &) override;
};