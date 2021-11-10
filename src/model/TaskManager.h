#pragma once

#include<map>
#include<vector>
#include<utility>
#include"Task.h"

class TaskManager {
public:
    TaskManager() { max_id_ = 0; }

    int Add(Task);

    void Edit(int, Task);

    void Complete(int);

    void Delete(int);

    std::map<int, Task> Show() const;

private:
    std::map<int, Task> tasks_;
    int max_id_;
};
