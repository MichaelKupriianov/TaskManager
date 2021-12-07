#include"StepMachine.h"
#include"Command.h"
#include"Context.h"
#include"Step.h"

StepMachine::StepMachine(std::shared_ptr<Factory> &factory) :
        factory_{factory} {}

Context StepMachine::Run() {
    std::unique_ptr<Step> step_{factory_->GetRootStep()};
    Context context;
    while (context.command() == Command::NONE) {
        step_ = std::move(step_->execute(context, factory_));
    }
    return context;
}