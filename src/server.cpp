#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "model/GRPCEndPoint.h"
#include "model/Model.h"
#include "logging/Initialisation.h"
#include "logging/Log.h"

int main() {
    ConsoleLogging{boost::log::trivial::error};
    FileLogging{"server.log", boost::log::trivial::debug};

    auto model = std::make_shared<model::Model>(
            std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>()));
    model::GRPCEndPoint service{model};
    std::string server_address("0.0.0.0:1234");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    LOG(info, "Server listening on " + server_address);

    server->Wait();
}