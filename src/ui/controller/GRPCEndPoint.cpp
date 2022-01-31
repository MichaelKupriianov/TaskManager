#include "GRPCEndPoint.h"
#include "Requests.pb.h"
#include "Responses.pb.h"

namespace ui {

bool GRPCEndPoint::AddTask(const model::Task& task) {
    AddTaskRequest request;
    request.set_allocated_task(new model::Task(task));
    AddTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddTask(&context, request, &response);
    return response.result();
}

bool GRPCEndPoint::AddSubTask(const model::Task& task, const model::TaskId& parent_id) {
    AddSubTaskRequest request;
    request.set_allocated_task(new model::Task(task));
    request.set_allocated_parent_id(new model::TaskId(parent_id));
    AddSubTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddSubTask(&context, request, &response);
    return response.result();
}

bool GRPCEndPoint::Edit(const model::TaskId &id, const model::Task& task) {
    EditRequest request;
    request.set_allocated_task(new model::Task(task));
    request.set_allocated_id(new model::TaskId(id));
    EditResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Edit(&context, request, &response);
    return response.result();
}

bool GRPCEndPoint::Complete(const model::TaskId &id) {
    CompleteRequest request;
    request.set_allocated_id(new model::TaskId(id));
    CompleteResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Complete(&context, request, &response);
    return response.result();
}

bool GRPCEndPoint::Delete(const model::TaskId &id) {
    DeleteRequest request;
    request.set_allocated_id(new model::TaskId(id));
    DeleteResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Delete(&context, request, &response);
    return response.result();
}

model::ManyTasksWithId GRPCEndPoint::ShowByLabel(const std::string& label, const model::TasksSortBy& sort_by) {
    ShowByLabelRequest request;
    request.set_label(label);
    request.set_sort_by(sort_by);
    ShowByLabelResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->ShowByLabel(&context, request, &response);
    return response.tasks();
}

model::ManyTasksWithId GRPCEndPoint::ShowParents(const model::TasksSortBy& sort_by) {
    ShowParentsRequest request;
    request.set_sort_by(sort_by);
    ShowParentsResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->ShowParents(&context, request, &response);
    return response.tasks();
}

model::CompositeTask GRPCEndPoint::ShowTask(const model::TaskId &id, const model::TasksSortBy& sort_by) {
    ShowTaskRequest request;
    request.set_allocated_id(new model::TaskId(id));
    request.set_sort_by(sort_by);
    ShowTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->ShowTask(&context, request, &response);
    return response.task();
}

model::ManyCompositeTasks GRPCEndPoint::ShowAll(const model::TasksSortBy& sort_by) {
    ShowAllRequest request;
    request.set_sort_by(sort_by);
    ShowAllResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->ShowAll(&context, request, &response);
    return response.tasks();
}

bool GRPCEndPoint::Save(const std::string &filename) {
    SaveRequest request;
    request.set_filename(filename);
    SaveResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Save(&context, request, &response);
    return response.result();
}

bool GRPCEndPoint::Load(const std::string &filename) {
    LoadRequest request;
    request.set_filename(filename);
    LoadResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Load(&context, request, &response);
    return response.result();
}
}