#include "StateMachine.h"

void StateMachine::Doing() {
    while (!context_.if_finished()) {
        state_ = std::move(state_->execute(context_));
    }
}