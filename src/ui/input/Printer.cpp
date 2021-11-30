#include"Printer.h"
#include<iostream>
#include<ctime>
#include<string>
#include"Converter.h"

void Printer::PrintSomeTasks(const std::vector<std::pair<TaskId, Task>> &tasks) {
    for (const auto &task: tasks) {
        PrintTask(task);
        std::cout << '\n';
    }
}

void Printer::PrintAllTasks(
        const std::vector<std::pair<std::pair<TaskId, Task>, std::vector<std::pair<TaskId, Task>>>> &tasks) {
    for (const auto &[task, children]: tasks) {
        PrintTask(task);
        std::cout << ":\n   ";
        PrintSomeTasks(children);
    }
}

void Printer::PrintTask(const std::pair<TaskId, Task> &task) {
    std::cout << "id: " << task.first.value() << ' ';
    std::cout << "Task: " << task.second.title() << " ";
    std::cout << "priority: " << Converter::PriorityToString(task.second.priority()) << " ";
    if (time_t date = task.second.date(); date != 0) std::cout << "date: " << ctime(&date) << " ";
    else std::cout << "date: none ";
    if (!task.second.label().empty()) std::cout << "label: " << task.second.label();
}
