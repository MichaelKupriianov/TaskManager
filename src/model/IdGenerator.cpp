#include "IdGenerator.h"

namespace model {
    api::TaskId IdGenerator::GenerateId() {
        api::TaskId id;
        id.set_value(max_id_++);
        return id;
    }
}