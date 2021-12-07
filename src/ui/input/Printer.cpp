#include"Printer.h"
#include<iostream>
#include<string>
#include"Converter.h"

void Printer::PrintSomeTasks(const ArrayOfIdWithTask &tasks, const std::string &introduction) {
    for (const auto &task: tasks) {
        std::cout << introduction;
        PrintTask(task);
        std::cout << '\n';
    }
}

void Printer::PrintAllTasks(
        const std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> &tasks) {
    if (tasks.empty()) {
        std::cout << "There are no outstanding tasks now.\n";
        return;
    }
    for (const auto &[task, children]: tasks) {
        PrintTask(task);
        if (!children.empty()) {
            std::cout << "  :\n";
            PrintSomeTasks(children, "   ");
        } else std::cout << '\n';
    }
}

void Printer::PrintException(const std::string &exception) {
    std::cout << exception << '\n';
}

void Printer::PrintTask(const std::pair<TaskId, Task> &task) {
    std::cout << "id: " << task.first.value();
    std::cout << ", title: " << task.second.title();
    std::cout << ", priority: " << Converter::PriorityToString(task.second.priority());
    std::cout << ", date: " << Converter::DateToString(task.second.date());
    if (!task.second.label().empty()) std::cout << ", label: " << task.second.label();
}
