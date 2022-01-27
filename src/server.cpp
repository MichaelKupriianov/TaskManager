#include "model/GRPCServerEndPoint.h"
#include "Service.grpc.pb.h"
#include "model/controller/DefaultModelController.h"
#include "model/TaskManager.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

int main() {
    std::unique_ptr<ModelController> model_controller = std::make_unique<DefaultModelController>(
            std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
            std::make_unique<TaskValidator>(),
            std::make_unique<persistence::PersistenceFactory>());

    GRPCServerEndPoint service { std::move(model_controller) };

    std::string server_address("0.0.0.0:8586");

    grpc::ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}