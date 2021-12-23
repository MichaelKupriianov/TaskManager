#include "Controller.h"
#include "ui/command/Command.h"
#include "ui/Context.h"

namespace ui {
    Controller::Controller(const std::shared_ptr<StateMachine>& machine,
                           const std::shared_ptr<command::Resources>& dependency)
            : step_machine_{machine}, dependency_(dependency) {}

    void Controller::Run() {
        Context context;
        while (true) {
            step_machine_->Run(context);
            command::Result result{context.command()->execute(dependency_)};
            if (result.finished) break;
            context.set_result(std::make_shared<command::Result>(result));
            context.set_command(std::nullopt);
        }
    }
}