#include"StepEdit.h"
#include"Factory.h"
#include"Reader.h"
#include"SubStepMachine.h"

std::unique_ptr<Step> StepEdit::execute(Context &context) {
    int id{reader_.ReadId()};
    SubStepMachine sub_machine;
    SubContext sub_context = sub_machine.Run(reader_);
    if (reader_.Confirm()) {
        context.set_command(Command::EDIT);
        context.set_id(id);
        context.set_task(sub_context.task());
    }
    return Factory::GetRootStep();
}
