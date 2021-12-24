#pragma once

#include "Task.pb.h"

namespace model {
    class IdGenerator {
    public:
        explicit IdGenerator(int v = 0) : max_id_(v) {}

        virtual proto::TaskId GenerateId();

        virtual ~IdGenerator() = default;
    private:
        int max_id_;
    };
}