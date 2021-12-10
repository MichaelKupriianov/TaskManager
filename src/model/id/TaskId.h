#pragma once

#include<optional>

class TaskId {
public:
    static std::optional<TaskId> Create(int);

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