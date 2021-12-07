#include"Factory.h"
#include"StepAdd.h"
#include"StepEdit.h"

std::unique_ptr<Step> Factory::CreateStep(TypeOfStep step) {
    StepRoot a{reader_};
    switch (step) {
        case TypeOfStep::ROOT:
            return std::unique_ptr<Step>(new StepRoot(reader_));
        case TypeOfStep::QUIT:
            return std::unique_ptr<Step>(new StepQuit(reader_));
        case TypeOfStep::HELP:
            return std::unique_ptr<Step>(new StepHelp(reader_));
        case TypeOfStep::ADD:
            return std::unique_ptr<Step>(new StepAdd(reader_));
        case TypeOfStep::EDIT:
            return std::unique_ptr<Step>(new StepEdit(reader_));
        case TypeOfStep::COMPLETE:
            return std::unique_ptr<Step>(new StepComplete(reader_));
        case TypeOfStep::DELETE:
            return std::unique_ptr<Step>(new StepDelete(reader_));
        case TypeOfStep::LABEL:
            return std::unique_ptr<Step>(new StepLabel(reader_));
        case TypeOfStep::SHOW:
            return std::unique_ptr<Step>(new StepShow(reader_));
        default:
            return nullptr;
    }
}

std::unique_ptr<Step> Factory::GetRootStep() {
    return std::unique_ptr<Step>(new StepRoot(reader_));
}