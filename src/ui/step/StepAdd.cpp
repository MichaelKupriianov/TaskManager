#include"StepAdd.h"
#include"Factory.h"
#include"ConsoleManager.h"

std::unique_ptr<Step> StepAdd::execute(Context &context) {
    context.set_local_finished(false);
    context.set_current_step("Add");

    std::unique_ptr<SubStep> step(Factory::GetNextSubStep());
    while (!context.local_finished()) {
        step = std::move(step->execute(context));
    }
    if (!reader.Confirm()) context.set_task({".."});
    return Factory::GetNextStep();
}
