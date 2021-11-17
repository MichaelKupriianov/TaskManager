#pragma once

#include"TaskId.h"

class IdGenerator {
public:
    explicit IdGenerator(int v = 0) : max_id_(v) {}

    virtual TaskId GenerateId() {
        return TaskId::Create(max_id_++);
    }
    virtual ~IdGenerator() = default;
private:
    int max_id_;
};
