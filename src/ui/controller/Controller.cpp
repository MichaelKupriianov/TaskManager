#include "Controller.h"
#include "ui/command/Command.h"
#include "ui/Context.h"

namespace ui {
    Controller::Controller(const std::shared_ptr<StateMachine>& machine,
                           const std::shared_ptr<command::Resources>& resources)
            : state_machine_{machine}, resources_(resources) {}

    void Controller::Run() {
        Context context;
        while (true) {
            state_machine_->Run(context);
            command::Result result{context.command()->execute(resources_)};
            if (result.finished) break;
            context.set_result(std::make_shared<command::Result>(result));
            context.set_command(std::nullopt);
        }
    }
}