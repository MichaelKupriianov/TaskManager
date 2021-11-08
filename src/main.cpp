#include <iostream>
#include<ctime>
#include"model/Task.h"
#include"model/TaskManager.h"

void Print(TaskManager &manager) {
    std::map<int, Task> tasks = manager.Show();
    for (auto t: tasks) {
        std::cout << "id: " << t.first << "   ";
        std::cout << "title: " << t.second.get_title() << "   ";
        std::cout << "priority: " << static_cast<int>(t.second.get_priority()) << "   ";
        time_t time = t.second.get_date();
        std::cout << "date: " << ctime(&time);
    }
    std::cout<<'\n';
}

int main() {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::HIGH, time(nullptr)));
    manager.Add(Task::Create("second", Task::Priority::LOU, time(nullptr) + 3600));
    manager.Add(Task::Create("third", Task::Priority::NONE, time(nullptr) + 3600 * 24));
    Print(manager);
    manager.Complete(2);
    manager.Delete(1);
    manager.Add(Task::Create("fourth", Task::Priority::HIGH, time(nullptr) + 5 * 24 * 3600));
    manager.Edit(0, Task::Create("fifth", Task::Priority::MEDIUM, time(nullptr) - 6 * 3600));
    Print(manager);
}
