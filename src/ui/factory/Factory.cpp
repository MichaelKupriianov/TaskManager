#include"Factory.h"

std::shared_ptr<Step> Factory::CreateStep(TypeOfStep step) {
    switch (step) {
        case TypeOfStep::ROOT:
            return std::shared_ptr<Step>{new StepRoot};
        case TypeOfStep::QUIT:
            return std::shared_ptr<Step>{new StepQuit};
        case TypeOfStep::HELP:
            return std::shared_ptr<Step>{new StepHelp};
        case TypeOfStep::ADD:
            return std::shared_ptr<Step>{new StepAdd};
        case TypeOfStep::ADDSUB:
            return std::shared_ptr<Step>{new StepAddSub};
        case TypeOfStep::EDIT:
            return std::shared_ptr<Step>{new StepEdit};
        case TypeOfStep::COMPLETE:
            return std::shared_ptr<Step>{new StepComplete};
        case TypeOfStep::DELETE:
            return std::shared_ptr<Step>{new StepDelete};
        case TypeOfStep::SHOW:
            return std::shared_ptr<Step>{new StepShow};
        case TypeOfStep::SHOWTASK:
            return std::shared_ptr<Step>{new StepShowTask};
        case TypeOfStep::SHOWLABEL:
            return std::shared_ptr<Step>{new StepShowLabel};
        default:
            return nullptr;
    }
}

std::shared_ptr<Step> Factory::GetRootStep() {
    return std::shared_ptr<Step>{
            new StepRoot};
}