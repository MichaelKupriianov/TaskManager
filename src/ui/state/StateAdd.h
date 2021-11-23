#pragma once

#include<memory>
#include"State.h"

class StateAdd : public State {
public:
    virtual std::unique_ptr<State> execute(Context &) override;
};

class StateAddTitle : public StateAdd {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateAddPriority : public StateAdd {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateAddTime : public StateAdd {
public:
    std::unique_ptr<State> execute(Context &) override;
};
