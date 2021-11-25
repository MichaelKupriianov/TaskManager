#include"StepEdit.h"
#include"Factory.h"
#include"ConsoleManager.h"

std::unique_ptr<Step> StepEdit::execute(Context &context) {
    context.set_local_finished(false);
    context.set_current_step("Edit");
    const int task_id(reader.ReadId(context.current_step()));
    context.set_id(task_id);

    std::unique_ptr<SubStep> step(Factory::GetNextSubStep());
    while (!context.local_finished()) {
        step = std::move(step->execute(context));
    }
    if (!reader.Confirm()) context.set_task({".."});
    return Factory::GetNextStep();
}
