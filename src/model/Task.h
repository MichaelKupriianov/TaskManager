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
    enum class State {
        NONE,
        DONE
    };
public:
    static Task Create(const std::string &, Priority = Priority::NONE, time_t = 0,
                       const std::string & = "", State = State::NONE);
public:
    std::string title() const { return title_; }
    Priority priority() const { return priority_; }
    time_t date() const { return due_date_; }
    std::string label() const { return label_; }
    Task::State state() const { return state_; }
public:
    Task(const Task &) = default;
    Task &operator=(const Task &) = delete;
    friend bool operator==(const Task &, const Task &);
private:
    Task(const std::string &, Priority, time_t, const std::string &, State);
private:
    const std::string title_;
    const Priority priority_;
    const time_t due_date_;
    const std::string label_;
    const State state_;
};

Task::Priority StringToPriority(const std::string &);
std::string PriorityToString(const Task::Priority);

