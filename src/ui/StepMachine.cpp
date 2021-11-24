#include "StepMachine.h"

void StepMachine::Run() {
    while (!context_.global_finished()) {
        state_ = std::move(state_->execute(context_));
    }
}