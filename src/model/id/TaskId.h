#pragma once

class TaskId {
public:
    static TaskId Create(int);
    static TaskId NotExistentId() { return TaskId(-1); }

    unsigned int value() const { return value_; }
public:
    TaskId(const TaskId &) = default;
    TaskId &operator=(const TaskId &) = delete;
private:
    explicit TaskId(unsigned int val) : value_(val) {}
private:
    const unsigned int value_;
};

bool operator<(const TaskId &, const TaskId &);
bool operator>(const TaskId &, const TaskId &);
bool operator==(const TaskId &, const TaskId &);