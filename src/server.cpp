#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "model/GRPCEndPoint.h"
#include "model/Model.h"
#include "logging/Initialisation.h"

int main() {
    InitialisationLoggingToConsole(boost::log::trivial::warning);
    InitialisationLoggingToFile("server.log", boost::log::trivial::info);

    auto model = std::make_shared<model::Model>(
            std::make_shared<model::TaskManager>(std::make_shared<model::IdGenerator>()));
    model::GRPCEndPoint service{model};
    std::string server_address("0.0.0.0:1234");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << '\n';

    server->Wait();
}