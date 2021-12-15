#pragma once

#include<string>
#include<ctime>
#include<memory>
#include"Task.pb.h"

class SubContext {
public:
    SubContext() : task_{new Task} {}
public:
    bool if_finished() const { return finished_; }
    std::shared_ptr<Task> task() const {return task_;}

    void finished() { finished_ = true; }
private:
    bool finished_ = false;
    std::shared_ptr<Task> task_;
};
