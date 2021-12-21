#pragma once

#include "Task.pb.h"

class IdGenerator {
public:
    explicit IdGenerator(int v = 0) : max_id_(v) {}

    virtual TaskId GenerateId();

    virtual ~IdGenerator() = default;
private:
    int max_id_;
};
