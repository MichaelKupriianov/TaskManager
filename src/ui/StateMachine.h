#pragma once

#include <memory>
#include "ui/step/Dependency.h"
#include "ui/command/Command.h"
#include "ui/Context.h"

namespace ui {
    class StateMachine {
    public:
        explicit StateMachine(const std::shared_ptr<step::Dependency>&);

        virtual std::shared_ptr<command::Command> GetCommand(Context& context);

        virtual ~StateMachine() = default;
    private:
        const std::shared_ptr<step::Dependency> dependency_;
    };
}