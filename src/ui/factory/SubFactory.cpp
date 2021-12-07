#include "SubFactory.h"

SubFactory::SubFactory(std::shared_ptr<Reader> &reader, Command command) :
        reader_(reader), command_{command} {}

std::unique_ptr<SubStep> SubFactory::GetRootSubStep() {
    return std::unique_ptr<SubStep>(new SubStepTitle(reader_, command_));
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepTitle &) {
    return std::unique_ptr<SubStep>(new SubStepPriority(reader_, command_));
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepPriority &) {
    return std::unique_ptr<SubStep>(new SubStepDate(reader_, command_));
}

std::unique_ptr<SubStep> SubFactory::GetNextSubStep(const SubStepDate &) {
    return std::unique_ptr<SubStep>(new SubStepDate(reader_, command_));
}
