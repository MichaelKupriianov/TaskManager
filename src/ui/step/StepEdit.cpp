#include"StepEdit.h"
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<Step> StepEdit::execute(Context &context) {
    std::unique_ptr<SubStep> state(Factory::CreateSubStep("id"));
    context.set_local_finished(false);
    context.set_current_step("Edit");

    while (!context.local_finished()) {
        state = std::move(state->execute(context));
    }
    if (!reader.Confirm()) context.set_task({".."});
    return Factory::CreateStep("command");
}
