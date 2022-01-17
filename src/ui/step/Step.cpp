#include "Step.h"
#include "ui/Factory.h"

namespace ui::step {

Root::Root(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Root::execute(Context& context) {
    if (context.result()->has_value())
        return factory_->CreateStep(step::Type::PRINT);

    Type type{view_->ReadCommand()};
    return factory_->CreateStep(type);
}

Quit::Quit(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Quit::execute(Context& context) {
    view_->PrintQuit();
    context.set_command(std::make_shared<command::Quit>());
    return factory_->GetInitialStep();
}

Help::Help(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Help::execute(Context& context) {
    view_->PrintHelp();
    return factory_->GetInitialStep();
}

Print::Print(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Print::execute(Context& context) {
    if (context.result()->error.has_value())
        view_->PrintError(context.result()->error.value());
    if (context.result()->composite_task.has_value())
        view_->PrintCompositeTask(context.result()->composite_task.value());
    if (context.result()->many_tasks.has_value())
        view_->PrintManyTasksWithId(context.result()->many_tasks.value());
    if (context.result()->many_composite_tasks.has_value())
        view_->PrintManyCompositeTasks(context.result()->many_composite_tasks.value());
    context.set_result();
    return factory_->GetInitialStep();
}

Complete::Complete(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Complete::execute(Context& context) {
    model::TaskId id{view_->ReadId(name())};
    if (view_->Confirm())
        context.set_command(std::make_shared<command::Complete>(id));
    return factory_->GetInitialStep();
}

std::string Complete::name() {return "[Complete Task]";}

Delete::Delete(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Delete::execute(Context& context) {
    model::TaskId id{view_->ReadId(name())};
    if (view_->Confirm())
        context.set_command(std::make_shared<command::Delete>(id));
    return factory_->GetInitialStep();
}

std::string Delete::name() {return "[Delete Task]";}

Save::Save(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Save::execute(Context& context) {
    const std::string filename{view_->ReadFilename(name())};
    if (view_->Confirm())
        context.set_command(std::make_shared<command::Save>(filename));
    return factory_->GetInitialStep();
}

std::string Save::name() {return "[Save to file]";}

Load::Load(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Load::execute(Context& context) {
    const std::string filename{view_->ReadFilename(name())};
    if (view_->Confirm())
        context.set_command(std::make_shared<command::Load>(filename));
    return factory_->GetInitialStep();
}

std::string Load::name() {return "[Load from file]";}
}
