#include <string>
#include <grpcpp/grpcpp.h>
#include "ModelService.grpc.pb.h"
#include "ui/controller/GRPCEndPoint.h"
#include "ui/StateMachine.h"
#include "ui/Factory.h"
#include "logging/Initialisation.h"
#include "logging/Log.h"

int main() {
    ConsoleLogging{boost::log::trivial::error};
    FileLogging{"client.log", boost::log::trivial::debug};

    std::string target_str = "localhost:1234";

    auto reader = std::make_shared<ui::Reader>();
    auto printer = std::make_shared<ui::Printer>();
    auto view = std::make_shared<ui::View>(reader, printer);
    auto factory = std::make_shared<ui::Factory>(view);

    auto initial_step{factory->GetInitialStep()};
    auto machine = std::make_shared<ui::StateMachine>(initial_step);

    std::shared_ptr<ui::Controller> controller =
            std::make_shared<ui::GRPCEndPoint>(
                    ModelService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())));
    LOG(info, "Client asks on " + target_str);

    machine->Run(controller);
}