#include "ui/Factory.h"
#include <cassert>

namespace ui {
    std::shared_ptr<step::Step> Factory::CreateStep(step::Type type) {
        switch (type) {
            case step::Type::QUIT:
                return std::make_shared<step::Quit>();
            case step::Type::HELP:
                return std::make_shared<step::Help>();
            case step::Type::PRINT:
                return std::make_shared<step::Print>();
            case step::Type::ADD:
                return std::make_shared<step::Add>();
            case step::Type::ADD_SUB:
                return std::make_shared<step::AddSub>();
            case step::Type::EDIT:
                return std::make_shared<step::Edit>();
            case step::Type::COMPLETE:
                return std::make_shared<step::Complete>();
            case step::Type::DELETE:
                return std::make_shared<step::Delete>();
            case step::Type::SHOW:
                return std::make_shared<step::Show>();
            case step::Type::SHOW_TASK:
                return std::make_shared<step::ShowTask>();
            case step::Type::SHOW_LABEL:
                return std::make_shared<step::ShowLabel>();
            case step::Type::SAVE:
                return std::make_shared<step::Save>();
            case step::Type::LOAD:
                return std::make_shared<step::Load>();
            default:
                assert(false);
        }
    }

    std::shared_ptr<step::Step> Factory::GetInitialStep() {
        return std::make_shared<step::Root>();
    }

    std::shared_ptr<step::SubStep> Factory::GetInitialSubStep() {
        return std::make_shared<step::SubStepTitle>();
    }

    std::shared_ptr<step::SubStep> Factory::GetNextSubStepFrom(const step::SubStepTitle&) {
        return std::make_shared<step::SubStepPriority>();
    }

    std::shared_ptr<step::SubStep> Factory::GetNextSubStepFrom(const step::SubStepPriority&) {
        return std::make_shared<step::SubStepDate>();
    }

    std::shared_ptr<step::SubStep> Factory::GetNextSubStepFrom(const step::SubStepDate&) {
        return std::make_shared<step::SubStepLabel>();
    }

    std::shared_ptr<step::SubStep> Factory::GetNextSubStepFrom(const step::SubStepLabel&) {
        return std::make_shared<step::SubStepLabel>();
    }
}