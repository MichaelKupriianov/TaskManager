#include "IdGenerator.h"

namespace model {
    proto::TaskId IdGenerator::GenerateId() {
        proto::TaskId id;
        id.set_value(max_id_++);
        return id;
    }
}