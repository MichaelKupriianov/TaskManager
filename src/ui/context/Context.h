#pragma once

#include<memory>
#include"id/TaskId.h"

class Context {
public:
    bool if_finished() const { return finished_; }
    TaskId id() const { return *task_id_; }

    void finished() { finished_ = true; }
    void set_id(int task_id);
private:
    bool finished_ = false;
    std::unique_ptr<TaskId> task_id_;
};
