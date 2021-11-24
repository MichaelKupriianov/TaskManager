#include"Factory.h"
#include"StepAdd.h"
#include"StepEdit.h"

std::unique_ptr<Step> Factory::CreateStep(const std::string &step) {
    if (step == "command") return std::unique_ptr<Step>(new StepCommand);
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

std::unique_ptr<SubStep> Factory::CreateSubStep(const std::string &step) {
    if (step == "id") return std::unique_ptr<SubStep>(new SubStepId);
    if (step == "title") return std::unique_ptr<SubStep>(new SubStepTitle);
    if (step == "priority") return std::unique_ptr<SubStep>(new SubStepPriority);
    if (step == "time") return std::unique_ptr<SubStep>(new SubStepTime);
    throw std::runtime_error("There is no such step");
}