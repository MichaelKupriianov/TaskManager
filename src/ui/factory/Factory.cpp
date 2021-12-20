#include"Factory.h"
#include<cassert>

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
        case TypeOfStep::ADD_SUB:
            return std::shared_ptr<Step>{new StepAddSub};
        case TypeOfStep::EDIT:
            return std::shared_ptr<Step>{new StepEdit};
        case TypeOfStep::COMPLETE:
            return std::shared_ptr<Step>{new StepComplete};
        case TypeOfStep::DELETE:
            return std::shared_ptr<Step>{new StepDelete};
        case TypeOfStep::SHOW:
            return std::shared_ptr<Step>{new StepShow};
        case TypeOfStep::SHOW_TASK:
            return std::shared_ptr<Step>{new StepShowTask};
        case TypeOfStep::SHOW_LABEL:
            return std::shared_ptr<Step>{new StepShowLabel};
        case TypeOfStep::SAVE:
            return std::shared_ptr<Step>{new StepSave};
        case TypeOfStep::LOAD:
            return std::shared_ptr<Step>{new StepLoad};
        default:
            assert(false);
    }
}

std::shared_ptr<Step> Factory::GetRootStep() {
    return std::shared_ptr<Step>{
            new StepRoot};
}