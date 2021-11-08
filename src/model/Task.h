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

    static Task Create(const std::string &, Priority, time_t);

    Task() = default;
    Task(const Task &) = default;
    Task &operator=(const Task &) = default;

    std::string get_title() {return title_;}
    Priority get_priority() {return priority_;}
    time_t get_date() {return due_date_;}

private:
    Task(const std::string &title, Priority priority, time_t date) :
            title_{title}, priority_{priority}, due_date_{date} {}

    std::string title_;
    Priority priority_;
    time_t due_date_;
};



