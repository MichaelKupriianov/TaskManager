#include"StepEdit.h"
#include"Factory.h"
#include"Reader.h"
#include"SubStepMachine.h"

std::unique_ptr<Step> StepEdit::execute(Context &context) {
    context.set_id(console_manager_.ReadId());
    SubStepMachine machine;
    machine.Run(console_manager_);
    if (!console_manager_.Confirm()) {}
    return Factory::GetRootStep();
}
