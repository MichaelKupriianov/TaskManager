#include"StepAdd.h"
#include"Factory.h"
#include"ConsoleManager.h"
#include"SubStepMachine.h"

std::unique_ptr<Step> StepAdd::execute(Context &context) {
    SubStepMachine machine;
    machine.Run(console_manager_);
    if (!console_manager_.Confirm()) {}
    return Factory::GetRootStep();
}
