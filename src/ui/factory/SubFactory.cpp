#include "SubFactory.h"

std::shared_ptr<SubStep> SubFactory::GetRootSubStep() {
    return std::shared_ptr<SubStep>(new SubStepTitle);
}

std::shared_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepTitle &) {
    return std::shared_ptr<SubStep>(new SubStepPriority);
}

std::shared_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepPriority &) {
    return std::shared_ptr<SubStep>(new SubStepDate);
}

std::shared_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepDate &) {
    return std::shared_ptr<SubStep>(new SubStepLabel);
}

std::shared_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepLabel &) {
    return std::shared_ptr<SubStep>(new SubStepLabel);
}