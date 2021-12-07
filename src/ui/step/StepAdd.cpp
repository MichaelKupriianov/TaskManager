#include"StepAdd.h"
#include"Factory.h"
#include"Reader.h"
#include"SubStepMachine.h"

std::unique_ptr<Step> StepAdd::execute(Context &context) {
    int parent_id{reader_.ReadParentId()};
    SubStepMachine sub_machine;
    SubContext sub_context = sub_machine.Run(reader_);
    if (reader_.Confirm()) {
        context.set_command(Command::ADD);
        context.set_id(parent_id);
        context.set_task(sub_context.task());
    }
    return Factory::GetRootStep();
}
