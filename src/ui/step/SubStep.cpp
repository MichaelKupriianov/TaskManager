#include "SubStep.h"
#include "Resources.h"
#include "Task.pb.h"

namespace ui::step {

std::shared_ptr<SubStep> SubStepTitle::execute(SubContext& context,
                                               const std::shared_ptr<Resources>& resources) {
    const std::string title{resources->view->ReadTitle((resources->command).value())};
    context.task()->set_title(title);
    return resources->factory->GetNextSubStepFrom(*this);
}

std::shared_ptr<SubStep> SubStepPriority::execute(SubContext& context,
                                                  const std::shared_ptr<Resources>& resources) {
    model::Task::Priority priority(resources->view->ReadPriority((resources->command).value()));
    context.task()->set_priority(priority);
    return resources->factory->GetNextSubStepFrom(*this);
}

std::shared_ptr<SubStep> SubStepDate::execute(SubContext& context,
                                              const std::shared_ptr<Resources>& resources) {
    google::protobuf::Timestamp date(resources->view->ReadDate((resources->command).value()));
    context.task()->set_allocated_date(new google::protobuf::Timestamp(date));
    return resources->factory->GetNextSubStepFrom(*this);
}

std::shared_ptr<SubStep> SubStepLabel::execute(SubContext& context,
                                               const std::shared_ptr<Resources>& resources) {
    const std::string label{resources->view->ReadLabel((resources->command).value())};
    context.task()->set_label(label);
    context.finished();
    return resources->factory->GetNextSubStepFrom(*this);
}
}