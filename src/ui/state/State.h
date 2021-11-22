#pragma once

#include<string>
#include<memory>

#include "Context.h"

class State {
public:
    virtual std::unique_ptr<State> execute(Context &) = 0;
};

std::unique_ptr<State> StringToCommand(const std::string &);

class StateCommand : public State {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateQuit : public State {
public:
    std::unique_ptr<State> execute(Context &) override;
};
