#include "Edit.h"
#include "Resources.h"
#include "ui/StateMachine.h"
#include "Task.pb.h"

namespace ui::step {
Edit::Edit() : type_{step::Type::EDIT} {}

std::shared_ptr<Step> Edit::execute(Context& context, const std::shared_ptr<Resources>& resources) {
    model::TaskId id{resources->view->ReadId(type_)};

    auto sub_resources = std::make_shared<Resources>(resources->factory, resources->view, type_);
    SubContext sub_context;
    StateMachine machine{sub_resources};
    machine.Run(sub_context);

    if (sub_resources->view->Confirm())
        context.set_command(std::make_shared<command::Edit>(id, *sub_context.task()));
    return resources->factory->GetInitialStep();
}
}