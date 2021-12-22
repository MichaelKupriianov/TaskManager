#pragma once

#include <memory>
#include "ui/StateMachine.h"
#include "ui/command/Dependency.h"

namespace ui {
    class Controller {
    public:
        Controller(const std::shared_ptr<StateMachine>&, const std::shared_ptr<command::Dependency>&);

        void Run();
    private:
        const std::shared_ptr<StateMachine> step_machine_;
        const std::shared_ptr<command::Dependency> dependency_;
    };
}