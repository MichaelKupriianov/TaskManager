#pragma once

#include <memory>
#include "step/Resources.h"
#include "Context.h"

namespace ui {
class StateMachine {
public:
    explicit StateMachine(const std::shared_ptr<step::Resources>&);
    virtual ~StateMachine() = default;

    virtual void Run(Context&);
    virtual void Run(SubContext&);
private:
    const std::shared_ptr<step::Resources> resources_;
};
}