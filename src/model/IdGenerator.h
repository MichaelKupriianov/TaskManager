#pragma once

#include "Task.pb.h"

namespace model {
class IdGenerator {
public:
    explicit IdGenerator(int max_id = 0) : max_id_(max_id) {}

    virtual model::TaskId GenerateId();

    virtual ~IdGenerator() = default;
private:
    int max_id_;
};
}