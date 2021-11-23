#pragma once

#include<string>
#include<ctime>
#include<memory>
#include"Task.h"

class Context {
public:
    bool finished() const { return finished_; }

    bool add_finished() const { return add_finished_; }

    std::string task_title() const { return task_->title(); }
    Task::Priority task_priority() const { return task_->priority(); }
    time_t task_date() const { return task_->date(); }
    std::string task_label() const { return task_->label(); }
    Task::State task_state() const { return task_->state(); }
public:
    void setFinished() { finished_ = true; }

    void setAddFinished(bool state) { add_finished_ = state; }

    void setTask(const std::string &, Task::Priority = Task::Priority::NONE, time_t = 0,
                 const std::string & = "", Task::State = Task::State::NONE);
private:
    bool finished_ = false;
private:
    bool add_finished_;
    std::unique_ptr<Task> task_;
};
