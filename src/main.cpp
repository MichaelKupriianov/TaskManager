#include "ui/StateMachine.h"
#include "ui/Factory.h"
#include "model/TaskManager.h"
#include "persistence/TaskPersister.h"

int main() {
    auto generator = std::make_shared<model::IdGenerator>();
    auto manager = std::make_shared<model::TaskManager>(generator);
    auto persister = std::make_shared<TaskPersister>();
    auto resources_for_controller = std::make_shared<ui::command::Resources>(manager, persister);

    auto reader = std::make_shared<ui::Reader>();
    auto printer = std::make_shared<ui::Printer>();
    auto view = std::make_shared<ui::View>(reader, printer);
    auto factory = std::make_shared<ui::Factory>(view);

    auto initial_step{factory->GetInitialStep()};
    auto machine = std::make_shared<ui::StateMachine>(initial_step);

    machine->Run(resources_for_controller);

    return 0;
}
