#include"Persister.h"
#include<fstream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/util/delimited_message_util.h>

bool Persister::Save(const std::vector<TransportationTask> &tasks, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto &task: tasks)
        google::protobuf::util::SerializeDelimitedToOstream(task, &file);
    file.close();
    return true;
}

std::optional<std::vector<TransportationTask>> Persister::Load(const std::string &filename) {
    std::vector<TransportationTask> result;
    std::ifstream file(filename);
    if (!file.is_open()) return std::nullopt;

    std::unique_ptr<google::protobuf::io::ZeroCopyInputStream> input =
            std::make_unique<google::protobuf::io::IstreamInputStream>(&file);
    TransportationTask task;
    while (google::protobuf::util::ParseDelimitedFromZeroCopyStream(&task, input.get(), nullptr)) {
        result.push_back(task);
        task.clear_id();
        task.clear_task();
        task.clear_parent();
    }
    return result;
}