#include "ui/StateMachine.h"
#include "ui/Factory.h"
#include "ui/controller/DefaultController.h"
#include "model/Model.h"
#include "logging/Initialisation.h"

int main() {
    InitialisationLoggingToConsole(boost::log::trivial::error);
    InitialisationLoggingToFile("main.log", boost::log::trivial::info);

    auto generator = std::make_shared<model::IdGenerator>();
    auto manager = std::make_shared<model::TaskManager>(generator);
    auto model = std::make_shared<model::Model>(manager);
    auto reader = std::make_shared<ui::Reader>();
    auto printer = std::make_shared<ui::Printer>();
    auto view = std::make_shared<ui::View>(reader, printer);
    auto factory = std::make_shared<ui::Factory>(view);

    auto initial_step{factory->GetInitialStep()};
    auto machine = std::make_shared<ui::StateMachine>(initial_step);

    std::shared_ptr<ui::Controller> controller = std::make_shared<ui::DefaultController>(model);
    machine->Run(controller);
    return 0;
}
