#include"Factory.h"

std::unique_ptr<Step> Factory::CreateStep(TypeOfStep step) {
    switch (step) {
        case TypeOfStep::ROOT:
            return std::unique_ptr<Step>(new StepRoot);
        case TypeOfStep::QUIT:
            return std::unique_ptr<Step>(new StepQuit);
        case TypeOfStep::HELP:
            return std::unique_ptr<Step>(new StepHelp);
        case TypeOfStep::ADD:
            return std::unique_ptr<Step>(new StepAdd);
        case TypeOfStep::EDIT:
            return std::unique_ptr<Step>(new StepEdit);
        case TypeOfStep::COMPLETE:
            return std::unique_ptr<Step>(new StepComplete);
        case TypeOfStep::DELETE:
            return std::unique_ptr<Step>(new StepDelete);
        case TypeOfStep::LABEL:
            return std::unique_ptr<Step>(new StepLabel);
        case TypeOfStep::SHOW:
            return std::unique_ptr<Step>(new StepShow);
        default:
            throw std::runtime_error("There is no such step");
    }
}

std::unique_ptr<Step> Factory::GetRootStep() {
    return std::unique_ptr<Step>(new StepRoot);
}