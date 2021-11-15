#pragma once

class TaskId {
public:
    static TaskId Create(int);
    unsigned int value() const { return value_; }
public:
    TaskId(const TaskId &) = default;
    TaskId &operator=(const TaskId &) = delete;

    friend bool operator<(const TaskId &, const TaskId &);
    friend bool operator==(const TaskId &, const TaskId &);
private:
    explicit TaskId(unsigned int val) : value_(val) {}
private:
    const unsigned int value_;
};