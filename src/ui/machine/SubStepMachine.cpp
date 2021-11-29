#include "SubStepMachine.h"

void SubStepMachine::Run(const Reader &manager) {
    while (!context_.if_finished()) {
        state_ = std::move(state_->execute(context_, manager));
    }
}