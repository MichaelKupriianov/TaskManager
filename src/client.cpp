#include <string>
#include <grpcpp/grpcpp.h>
#include "Service.grpc.pb.h"
#include "ui/controller/GRPCEndPoint.h"
#include "ui/StateMachine.h"
#include "ui/Factory.h"

int main() {
    std::string target_str = "localhost:1488";

    auto reader = std::make_shared<ui::Reader>();
    auto printer = std::make_shared<ui::Printer>();
    auto view = std::make_shared<ui::View>(reader, printer);
    auto factory = std::make_shared<ui::Factory>(view);

    auto initial_step{factory->GetInitialStep()};
    auto machine = std::make_shared<ui::StateMachine>(initial_step);

    std::shared_ptr<ui::Controller> controller =
            std::make_shared<ui::GRPCEndPoint>(ModelControllerService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())));

    machine->Run(controller);
}