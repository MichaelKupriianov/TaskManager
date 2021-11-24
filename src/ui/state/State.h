#pragma once

#include<memory>
#include"Context.h"
#include"Reader.h"

class State {
public:
    virtual std::unique_ptr<State> execute(Context &) = 0;
protected:
    Reader reader;
};

class StateCommand : public State {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateQuit : public State {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateHelp : public State {
public:
    std::unique_ptr<State> execute(Context &) override;
};

class StateEdit : public State {
public:
    std::unique_ptr<State> execute(Context &) override {}
};

class StateComplete : public State {
public:
    std::unique_ptr<State> execute(Context &) override {}
};

class StateDelete : public State {
public:
    std::unique_ptr<State> execute(Context &) override {}
};

class StateLabel : public State {
public:
    std::unique_ptr<State> execute(Context &) override {}
};

class StateShow : public State {
public:
    std::unique_ptr<State> execute(Context &) override {}
};