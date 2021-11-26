#include "SubStepMachine.h"

void SubStepMachine::Run(const ConsoleManager &manager) {
    while (!context_.if_finished()) {
        state_ = std::move(state_->execute(context_, manager));
    }
}