#include"StepEdit.h"
#include"SubStepMachine.h"
#include"SubContext.h"
#include"SubFactory.h"
#include"Factory.h"

StepEdit::StepEdit(std::shared_ptr<Reader> &reader) :
        reader_{reader}, command_{Command::EDIT} {}

std::unique_ptr<Step> StepEdit::execute(Context &context, std::shared_ptr<Factory> &factory) {
    int id{reader_->ReadId(command_)};
    std::shared_ptr<SubFactory> sub_factory(new SubFactory(reader_, command_));
    SubStepMachine sub_machine{sub_factory};
    SubContext sub_context = sub_machine.Run();
    if (reader_->Confirm()) {
        context.set_command(Command::EDIT);
        context.set_id(id);
        context.set_task(sub_context.task());
    }
    return factory->GetRootStep();
}
