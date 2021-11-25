#include"Factory.h"

std::unique_ptr<Step> Factory::CreateStep(const std::string &step) {
    if (step == "quit") return std::unique_ptr<Step>(new StepQuit);
    if (step == "help") return std::unique_ptr<Step>(new StepHelp);
    if (step == "add") return std::unique_ptr<Step>(new StepAdd);
    if (step == "edit") return std::unique_ptr<Step>(new StepEdit);
    if (step == "complete") return std::unique_ptr<Step>(new StepComplete);
    if (step == "delete") return std::unique_ptr<Step>(new StepDelete);
    if (step == "label") return std::unique_ptr<Step>(new StepLabel);
    if (step == "show") return std::unique_ptr<Step>(new StepShow);
    throw std::runtime_error("There is no such step");
}

std::unique_ptr<Step> Factory::GetNextStep() {
    return std::unique_ptr<Step>(new StepCommand);
}

std::unique_ptr<SubStep> Factory::GetNextSubStep() {
    return std::unique_ptr<SubStep>(new SubStepTitle);
}

std::unique_ptr<SubStep> Factory::GetNextSubStep(const SubStepTitle &) {
    return std::unique_ptr<SubStep>(new SubStepPriority);
}

std::unique_ptr<SubStep> Factory::GetNextSubStep(const SubStepPriority &) {
    return std::unique_ptr<SubStep>(new SubStepTime);
}

std::unique_ptr<SubStep> Factory::GetNextSubStep(const SubStepTime &) {
    return std::unique_ptr<SubStep>(new SubStepTime);
}
