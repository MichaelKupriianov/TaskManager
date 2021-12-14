#pragma once

#include<string>
#include<ctime>
#include<memory>
#include"Task.h"

class SubContext {
public:
    bool if_finished() const { return finished_; }
    std::string task_title() const { return task_->title(); }
    Task::Priority task_priority() const { return task_->priority(); }
    time_t task_date() const { return task_->date(); }
    Task task() const {return *task_;}

    void finished() { finished_ = true; }
    void set_task(const Task::Arguments &);
private:
    bool finished_ = false;
    std::unique_ptr<Task> task_;
};
