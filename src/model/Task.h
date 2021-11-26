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

    enum class Condition {
        NONE,
        COMPLETED
    };

    struct Arguments {
        static Arguments Create(const std::string &, Priority = Priority::NONE, time_t = 0,
                  const std::string & = "", Condition = Condition::NONE);
        const std::string &title_;
        const Priority priority_;
        const time_t date_;
        const std::string &label_;
        const Condition state_;
    private:
        Arguments(const std::string &, Priority, time_t, const std::string &, Condition);
    };
public:
    static Task Create(const Arguments &);

    std::string title() const { return title_; }
    Priority priority() const { return priority_; }
    time_t date() const { return date_; }
    std::string label() const { return label_; }
    Task::Condition state() const { return state_; }

    Task(const Task &) = default;
    Task &operator=(const Task &) = delete;
    friend bool operator==(const Task &, const Task &);
private:
    Task(const Arguments &);
private:
    const std::string title_;
    const Priority priority_;
    const time_t date_;
    const std::string label_;
    const Condition state_;
};
