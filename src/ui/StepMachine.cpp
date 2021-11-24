#include "StepMachine.h"

void StepMachine::Doing() {
    while (!context_.finished()) {
        state_ = std::move(state_->execute(context_));
    }
}