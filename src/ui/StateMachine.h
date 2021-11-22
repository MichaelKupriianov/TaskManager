#pragma once

#include <memory>

#include"State.h"
#include"Context.h"

class StateMachine {
public:
    StateMachine() : state_(new StateCommand) {}

    void Doing();

private:
    std::unique_ptr<State> state_;
    Context context_;
};
