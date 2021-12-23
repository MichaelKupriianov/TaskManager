#include "ui/controller/Controller.h"

int main() {
    auto generator = std::make_shared<model::IdGenerator>();
    auto manager = std::make_shared<model::TaskManager>(generator);
    auto persister = std::make_shared<TaskPersister>();
    auto resources_for_controller = std::make_shared<ui::command::Resources>(manager, persister);

    auto reader = std::make_shared<ui::Reader>();
    auto printer = std::make_shared<ui::Printer>();
    auto view = std::make_shared<ui::View>(reader, printer);
    auto factory = std::make_shared<ui::Factory>();
    auto resources_for_machine = std::make_shared<ui::step::Resources>(factory, view);

    auto machine = std::make_shared<ui::StateMachine>(resources_for_machine);

    ui::Controller controller{machine, resources_for_controller};
    controller.Run();
    return 0;
}
