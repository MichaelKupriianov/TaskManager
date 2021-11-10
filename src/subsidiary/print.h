#pragma once

#include<iostream>
#include<map>
#include"../model/id/TaskId.h"
#include"../model/Task.h"
#include"../model/TaskManager.h"
#include"convert.h"

void Print(const TaskId &id) {
    std::cout << "id: " << id.value() << "   ";
}

void Print(const Task &task) {
    std::cout << "title: " << task.get_title() << "   ";
    std::cout << "priority: " << ToString(task.get_priority()) << "   ";
    time_t time = task.get_date();
    std::cout << "date: " << ctime(&time);
}

void Print(const TaskManager &manager) {
    std::map<TaskId, Task> tasks = manager.Show();
    for (auto t: tasks) {
        Print(t.first);
        Print(t.second);
    }
    std::cout << '\n';
}