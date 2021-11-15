#pragma once

#include"TaskId.h"

class IdGenerator {
public:
    IdGenerator() : max_id(0) {}

    TaskId GenerateId() {
        return TaskId::Create(max_id++);
    }
private:
    int max_id;
};
