#pragma once

#include<iostream>
#include<map>
#include"id/TaskId.h"
#include"Task.h"
#include"TaskManager.h"
#include"convert.h"

void Print(const TaskId &id) {
    std::cout << "id: " << id.value() << "   ";
}

void Print(const Task &task) {
    std::cout << "title: " << task.title() << "   ";
    std::cout << "priority: " << ToString(task.priority()) << "   ";
    time_t time = task.date();
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