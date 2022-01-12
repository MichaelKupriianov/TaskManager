#include "IdGenerator.h"

namespace model {
model::TaskId IdGenerator::GenerateId() {
    model::TaskId id;
    id.set_value(max_id_++);
    return id;
}
}