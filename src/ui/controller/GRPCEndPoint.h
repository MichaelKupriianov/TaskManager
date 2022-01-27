#pragma once

#include <memory>
#include <utility>
#include <grpcpp/grpcpp.h>
#include "ModelService.grpc.pb.h"
#include "model/Model.h" //?
#include "Controller.h"  //?

namespace ui {
class GRPCEndPoint : public model::Model {
public:
    explicit GRPCEndPoint(const std::shared_ptr<ModelService::StubInterface>& stub) :
            stub_{stub} {}

    bool AddTask(const model::Task& task) override;
    bool AddSubTask(const model::Task& task, const model::TaskId& id) override;
    bool Edit(const model::TaskId& id, const model::Task& task) override;
    bool Complete(const model::TaskId& id) override;
    bool Delete(const model::TaskId& id) override;

    model::ManyTasksWithId ShowByLabel(const std::string& label, const model::TasksSortBy&) override;
    model::ManyTasksWithId ShowParents(const model::TasksSortBy&) override;
    model::CompositeTask ShowTask(const model::TaskId& id, const model::TasksSortBy&) override;
    model::ManyCompositeTasks ShowAll(const model::TasksSortBy&) override;

    bool Save(const std::string& filename) override;
    bool Load(const std::string& filename) override;
private:
    std::shared_ptr<ModelService::StubInterface> stub_;
};
}
