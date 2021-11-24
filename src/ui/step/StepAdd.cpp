#include"StepAdd.h"
#include"Factory.h"
#include"Reader.h"

std::unique_ptr<Step> StepAdd::execute(Context &context) {
    std::unique_ptr<SubStep> state(Factory::CreateSubStep("title"));
    context.set_local_finished(false);
    context.set_current_step("Add");

    while (!context.local_finished()) {
        state = std::move(state->execute(context));
    }
    if (!reader.Confirm()) context.set_task({".."});
    return Factory::CreateStep("command");
}
