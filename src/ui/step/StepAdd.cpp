#include"StepAdd.h"
#include"SubStepMachine.h"
#include"SubContext.h"
#include"Factory.h"
#include"SubFactory.h"

StepAdd::StepAdd(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::ADD} {}

std::unique_ptr<Step> StepAdd::execute(Context &context, std::shared_ptr<Factory> &factory) {
    int parent_id{reader_->ReadParentId(command_)};
    std::shared_ptr<SubFactory> sub_factory(new SubFactory(reader_, command_));
    SubStepMachine sub_machine{sub_factory};
    SubContext sub_context = sub_machine.Run();
    if (reader_->Confirm()) {
        context.set_command(Command::ADD);
        context.set_id(parent_id);
        context.set_task(sub_context.task());
    }
    return factory->GetRootStep();
}
