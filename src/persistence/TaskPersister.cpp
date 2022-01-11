#include "TaskPersister.h"
#include <fstream>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>

bool TaskPersister::Save(const proto::ArrayHierarchicalTasks& tasks, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto &[id, task]: tasks) {
        google::protobuf::util::SerializeDelimitedToOstream(id, &file);
        google::protobuf::util::SerializeDelimitedToOstream(task, &file);
    }
    file.close();
    return true;
}

std::optional<proto::ArrayHierarchicalTasks> TaskPersister::Load(const std::string& filename) {
    proto::ArrayHierarchicalTasks result;
    std::ifstream file(filename);
    if (!file.is_open()) return std::nullopt;

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file);
    proto::HierarchicalTask task;
    proto::TaskId id;

    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&id, input.get(), nullptr) &&
           google::protobuf::util::ParseDelimitedFromZeroCopyStream(&task, input.get(), nullptr)) {
        result.push_back({id, task});
        task.clear_parent();
        task.clear_task();
        id.clear_value();
    }
    file.close();
    return result;
}