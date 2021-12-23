#include "Add.h"
#include "Resources.h"
#include "ui/StateMachine.h"
#include "Task.pb.h"

namespace ui::step {

    Add::Add() : type_{Type::ADD} {}

    std::shared_ptr<Step> Add::execute(Context& context, const std::shared_ptr<Resources>& resources) {
        auto sub_resources = std::make_shared<Resources>(resources->factory, resources->view, type_);
        SubContext sub_context;
        StateMachine machine{sub_resources};
        machine.Run(sub_context);

        if (sub_resources->view->Confirm())
            context.set_command(std::make_shared<command::Add>(*sub_context.task()));
        return resources->factory->GetInitialStep();
    }

    AddSub::AddSub() : type_{Type::ADD_SUB} {}

    std::shared_ptr<Step> AddSub::execute(Context& context, const std::shared_ptr<Resources>& resources) {
        api::TaskId parent_id{resources->view->ReadParentId(type_)};

        auto sub_resources = std::make_shared<Resources>(resources->factory, resources->view, type_);
        SubContext sub_context;
        StateMachine machine{sub_resources};
        machine.Run(sub_context);

        if (sub_resources->view->Confirm())
            context.set_command(std::make_shared<command::AddSub>(*sub_context.task(), parent_id));
        return resources->factory->GetInitialStep();
    }
}