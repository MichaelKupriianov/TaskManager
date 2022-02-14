#include <string>
#include <grpcpp/grpcpp.h>
#include "ModelService.grpc.pb.h"
#include "ui/controller/GRPCEndPoint.h"
#include "ui/StateMachine.h"
#include "ui/Factory.h"
#include "logging/Initialisation.h"
#include "logging/Log.h"
#include <boost/program_options.hpp>

namespace options = boost::program_options;

int main(int argc, char** argv) {
    std::string host, port;
    options::options_description general_options("Available options");
    general_options.add_options()
            ("debug", "debug logging mode")
            ("host,h", options::value<std::string>(&host)->default_value("localhost"))
            ("port,p", options::value<std::string>(&port)->default_value("1234"));

    options::variables_map arguments;
    options::store(options::parse_command_line(argc, argv, general_options), arguments);
    options::notify(arguments);

    ConsoleLogging{boost::log::trivial::error};

    (arguments.find("debug") != arguments.end()) ? FileLogging{"client.log", boost::log::trivial::debug} :
                                                   FileLogging{"client.log", boost::log::trivial::info};

    std::string target_str = host + ":" + port;

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