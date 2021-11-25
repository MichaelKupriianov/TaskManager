#include"StepEdit.h"
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<Step> StepEdit::execute(Context &context) {
    std::unique_ptr<SubStep> step(Factory::GetNextSubStep());
    context.set_local_finished(false);
    context.set_current_step("Edit");

    while (!context.local_finished()) {
        step = std::move(step->execute(context));
    }
    if (!reader.Confirm()) context.set_task({".."});
    return Factory::GetNextStep();
}
