#include "Persister.h"
#include <fstream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>

bool Persister::Save(const Tasks &tasks, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto &[id, task]: tasks) {
        google::protobuf::util::SerializeDelimitedToOstream(id, &file);
        google::protobuf::util::SerializeDelimitedToOstream(task, &file);
    }
    file.close();
    return true;
}

std::optional<Persister::Tasks> Persister::Load(const std::string &filename) {
    Tasks result;
    std::ifstream file(filename);
    if (!file.is_open()) return std::nullopt;

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file);
    FamilyTask task;
    TaskId id;

    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&id, input.get(), nullptr)) {
        google::protobuf::util::ParseDelimitedFromZeroCopyStream(&task, input.get(), nullptr);
        result.push_back({id, task});
        task.clear_parent();
        task.clear_task();
        id.clear_value();
    }
    return result;
}