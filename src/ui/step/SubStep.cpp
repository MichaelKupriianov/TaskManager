#include "SubStep.h"
#include "dependency/DependencyForSubSteps.h"
#include "Task.pb.h"

std::shared_ptr<SubStep> SubStepTitle::execute(SubContext &context,
                                               const std::shared_ptr<DependencyForSubSteps> &dependency) {
    const std::string title(dependency->view()->ReadTitle(dependency->command()));
    context.task()->set_title(title);
    return dependency->factory()->GetNextSubStep(*this);
}

std::shared_ptr<SubStep> SubStepPriority::execute(SubContext &context,
                                                  const std::shared_ptr<DependencyForSubSteps> &dependency) {
    Task::Priority priority(dependency->view()->ReadPriority(dependency->command()));
    context.task()->set_priority(priority);
    return dependency->factory()->GetNextSubStep(*this);
}

std::shared_ptr<SubStep> SubStepDate::execute(SubContext &context,
                                              const std::shared_ptr<DependencyForSubSteps> &dependency) {
    google::protobuf::Timestamp date(dependency->view()->ReadDate(dependency->command()));
    context.task()->set_allocated_date(new google::protobuf::Timestamp(date));
    return dependency->factory()->GetNextSubStep(*this);
}

std::shared_ptr<SubStep> SubStepLabel::execute(SubContext &context,
                                               const std::shared_ptr<DependencyForSubSteps> &dependency) {
    const std::string label(dependency->view()->ReadLabel(dependency->command()));
    context.task()->set_label(label);
    context.finished();
    return dependency->factory()->GetNextSubStep(*this);
}