#pragma once

#include <memory>
#include "Context.h"
#include "step/Step.h"

namespace ui {
class StateMachine {
public:
    explicit StateMachine(const std::shared_ptr<step::Step>& initial_step);
    virtual ~StateMachine() = default;

    virtual void Run(const std::shared_ptr<command::Resources>&);
    virtual void Run(Context &);
private:
    const std::shared_ptr<step::Step> initial_step_;
};
}