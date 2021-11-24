#pragma once

#include<string>
#include<ctime>
#include<memory>
#include"Task.h"

class Context {
public:
    bool global_finished() const { return global_finished_; }

    bool local_finished() const { return local_finished_; }

    std::string current_step() const { return current_step_; }

    int id() const { return task_id_; }
    std::string task_title() const { return task_->title(); }
    Task::Priority task_priority() const { return task_->priority(); }
    time_t task_date() const { return task_->date(); }
    std::string task_label() const { return task_->label(); }
    Task::State task_state() const { return task_->state(); }
public:
    void set_global_finished() { global_finished_ = true; }

    void set_local_finished(bool state) { local_finished_ = state; }

    void set_current_step(std::string step) { current_step_ = step; }

    void set_id(int task_id) { task_id_ = task_id; }
    void set_task(const Task::Parameter &);
private:
    bool global_finished_ = false;
    bool local_finished_;
    std::string current_step_;

    int task_id_;
    std::unique_ptr<Task> task_;
};
