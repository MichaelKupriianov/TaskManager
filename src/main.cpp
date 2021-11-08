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
    std::cout << '\n';
}

time_t ToTime(std::string date) {
    tm time = {};
    std::string pattern{"%H:%M %d/%m/%Y"};
    strptime(date.c_str(), pattern.c_str(), &time);
    return mktime(&time);
}

int main() {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::HIGH, ToTime("12:00 17/12/2021")));
    manager.Add(Task::Create("second", Task::Priority::LOU, ToTime("23:00 12/11/2021")));
    manager.Add(Task::Create("third", Task::Priority::NONE, ToTime("11:15 5/12/2021")));
    Print(manager);
    manager.Complete(2);
    manager.Delete(1);
    manager.Add(Task::Create("fourth", Task::Priority::HIGH, ToTime("14:00 10/5/2022")));
    manager.Edit(0, Task::Create("fifth", Task::Priority::MEDIUM, ToTime("5:05 3/4/2022")));
    Print(manager);
}
