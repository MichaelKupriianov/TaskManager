#include "SubFactory.h"

std::unique_ptr<SubStep> SubFactory::GetRootSubStep() {
    return std::unique_ptr<SubStep>(new SubStepTitle);
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepTitle &) {
    return std::unique_ptr<SubStep>(new SubStepPriority);
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepPriority &) {
    return std::unique_ptr<SubStep>(new SubStepDate);
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepDate &) {
    return std::unique_ptr<SubStep>(new SubStepDate);
}
