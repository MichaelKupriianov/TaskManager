#include"IdGenerator.h"

TaskId IdGenerator::GenerateId() {
    TaskId id;
    id.set_value(max_id_++);
    return id;
}
