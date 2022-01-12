#include "Step.h"
#include "Resources.h"

namespace ui::step {

std::shared_ptr<Step> Root::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    if (context.has_result())
        return resources->factory->CreateStep(step::Type::PRINT);

    Type type{resources->view->ReadCommand()};
    return resources->factory->CreateStep(type);
}

std::shared_ptr<Step> Quit::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    resources->view->PrintQuit();
    context.set_command(std::make_shared<command::Quit>());
    return resources->factory->GetInitialStep();
}

std::shared_ptr<Step> Help::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    resources->view->PrintHelp();
    return resources->factory->GetInitialStep();
}

std::shared_ptr<Step> Print::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    if (context.result()->error.has_value())
        resources->view->PrintError(context.result()->error.value());
    if (context.result()->task.has_value())
        resources->view->PrintCompositeTask(context.result()->task.value());
    if (context.result()->array.has_value())
        resources->view->PrintArraySimpleTasks(context.result()->array.value());
    if (context.result()->all_tasks.has_value())
        resources->view->PrintArrayCompositeTasks(context.result()->all_tasks.value());
    context.set_result(std::nullopt);
    return resources->factory->GetInitialStep();
}

Complete::Complete() : type_{step::Type::COMPLETE} {}

std::shared_ptr<Step> Complete::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    model::TaskId id{resources->view->ReadId(type_)};
    if (resources->view->Confirm())
        context.set_command(std::make_shared<command::Complete>(id));
    return resources->factory->GetInitialStep();
}

Delete::Delete() : type_{step::Type::DELETE} {}

std::shared_ptr<Step> Delete::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    model::TaskId id{resources->view->ReadId(type_)};
    if (resources->view->Confirm())
        context.set_command(std::make_shared<command::Delete>(id));
    return resources->factory->GetInitialStep();
}

Save::Save() : type_{step::Type::SAVE} {}

std::shared_ptr<Step> Save::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    const std::string filename{resources->view->ReadFilename(type_)};
    if (resources->view->Confirm())
        context.set_command(std::make_shared<command::Save>(filename));
    return resources->factory->GetInitialStep();
}

Load::Load() : type_{step::Type::LOAD} {}

std::shared_ptr<Step> Load::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    const std::string filename{resources->view->ReadFilename(type_)};
    if (resources->view->Confirm())
        context.set_command(std::make_shared<command::Load>(filename));
    return resources->factory->GetInitialStep();
}
}
