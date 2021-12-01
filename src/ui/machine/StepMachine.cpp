#include"StepMachine.h"
#include"Command.h"

Context StepMachine::Run() {
    Context context;
    while(context.command() == Command::NONE) {
        state_=std::move(state_->execute(context));
    }
    return context;
}