#pragma once

#include"State.h"

class StateAdd : public State {
    std::unique_ptr<State> execute(Context &) override {}
};

time_t StringToTime(const std::string &);
std::string TimeToString(time_t time);
