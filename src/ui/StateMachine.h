#pragma once

#include <memory>
#include"State.h"
#include"Factory.h"
#include"Context.h"

class StateMachine {
public:
    StateMachine() : state_(Factory::CreateState("command")) {}

    void Doing();
private:
    std::unique_ptr<State> state_;
    Context context_;
};
