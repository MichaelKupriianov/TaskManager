#pragma once

class TaskId {
public:
    unsigned int value() const { return value_; }

    static TaskId Create(int);

    TaskId(const TaskId &) = default;
    TaskId &operator=(const TaskId &) = delete;

    friend bool operator<(const TaskId &, const TaskId &);
    friend bool operator==(const TaskId &, const TaskId &);

private:
    explicit TaskId(unsigned int val) : value_(val) {}

    const unsigned int value_;
};