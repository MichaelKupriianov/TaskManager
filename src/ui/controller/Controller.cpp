#include "Controller.h"
#include "Command.h"

Controller::Controller(const std::shared_ptr<StepMachine> &machine, const std::shared_ptr<TaskManager> &manager)
        : step_machine_{machine}, task_manager_{manager} {}

void Controller::Run() {
    while (true) {
        std::shared_ptr<Command> command{step_machine_->GetCommand()};
        if (!command->execute(task_manager_)) break;
    }
}