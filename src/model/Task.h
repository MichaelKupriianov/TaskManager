#pragma once

#include<string>
#include<ctime>

class Task {
public:
    enum class Priority {
        HIGH,
        MEDIUM,
        LOU,
        NONE
    };
public:
    Task(const Task &) = default;
    Task &operator=(const Task &) = delete;
public:
    static Task Create(const std::string &, Priority, time_t);

    std::string title() const { return title_; }
    Priority priority() const { return priority_; }
    time_t date() const { return due_date_; }
private:
    Task(const std::string &title, Priority priority, time_t date) :
            title_{title}, priority_{priority}, due_date_{date} {}
private:
    const std::string title_;
    const Priority priority_;
    const time_t due_date_;
};



